#include "EInvaderGroup.h"
#include "Engine.h"
#include <cassert>

using namespace Common;

namespace SpaceInvaders
{
  void EInvaderGroup::update(const float& deltaTime)
  {
    const bool changeAnimFrame = isAnimationFrameChangeNeeded(deltaTime);
    const bool changeDirection = isChangeDirectionNeeded(deltaTime);

    for (int i = 0; i < GameConfig::InvaderTotalCount; i++)
    {
      shared_ptr<EInvader> currInvader = m_invaders[i];
      if (currInvader->isAlive())
      {
        currInvader->update(deltaTime);
        if (changeAnimFrame)
        {
          currInvader->changeAnimationFrame();
        }
        if (changeDirection)
        {
          currInvader->changeDirection();
          currInvader->setPosition(currInvader->getPosition() + Vector2f(0.f, GameConfig::InvaderGroupMoveDownDistance));
        }
      }      
    }
  }

  void EInvaderGroup::draw(Graphics& graphics)
  {
    for (int i = 0; i < GameConfig::InvaderTotalCount; i++)
    {
      m_invaders[i]->draw(graphics);
    }
  }

  EInvader* EInvaderGroup::tryFindCollidingInvader(const ECannonRocket& rocket) const
  {
    // Iterate backwards since rocket will probably hit bottom invaders first
    for (int i = GameConfig::InvaderTotalCount - 1; i >= 0; i--)
    {
      const shared_ptr<EInvader> currInv = m_invaders[i];
      if (currInv->isAlive() && currInv->isColliding(rocket))
      {
        return currInv.get();
      }
    }
    return nullptr;
  }

  EInvader& EInvaderGroup::getClosestAliveInvaderAtPosition(const int column, const int row)
  {
    shared_ptr<EInvader> invader = getInvader(column, row);    
    if (invader->isAlive() == false)
    {
      int closestAliveIndex = -1;
      const float closestDistance = 10000.f;

      for (int y = 0; y < GameConfig::InvaderRows; y++)
      {
        for (int x = 0; x < GameConfig::InvaderColumns; x++)
        {
          const shared_ptr<EInvader> currInvader = getInvader(x, y);
          if (currInvader->isAlive() && (invader->getPosition() - currInvader->getPosition()).length() < closestDistance)
          {
            closestAliveIndex = y * GameConfig::InvaderColumns + x;
          }
        }
      }
      
      assert(closestAliveIndex >= 0);
      invader = m_invaders[closestAliveIndex];
      assert(invader->isAlive());
    }
    return *invader;
  }

  void EInvaderGroup::reset(const bool isGameOver)
  {
    if (isGameOver)
    {
      m_currentInvaderVelocity = GameConfig::InvaderStartingVelocity;
    }

    for (int y = GameConfig::InvaderRows-1; y >= 0; y--)
    {
      for (int x = 0; x < GameConfig::InvaderColumns; x++)
      {
        shared_ptr<EInvader> currInvader = getInvader(x, y);
        currInvader->setPosition(getInvaderStartPosition(currInvader->getType(), y, x));
        currInvader->setIsAlive(true);
        currInvader->setDrawingCooldown(getDrawingCooldown(x, GameConfig::InvaderRows - 1 - y));
        currInvader->setVelocity(Vector2f(m_currentInvaderVelocity, 0));
      }
    }
  }
  
  float EInvaderGroup::getDrawingCooldown(const int column, const int row)
  {
    return GameConfig::InvaderColumns*row*GameConfig::InvaderDrawingCooldown + column*GameConfig::InvaderDrawingCooldown;
  }

  EInvader* EInvaderGroup::getFirstAliveInvaderFromTheBottom() const
  {
    for (int y = GameConfig::InvaderRows-1; y >= 0; y--)
    {
      for (int x = 0; x < GameConfig::InvaderColumns; x++)
      {
        shared_ptr<EInvader> currInvader = getInvader(x, y);
        if (currInvader->isAlive())
        {
          return currInvader.get();
        }
      }
    }
    return nullptr;
  }

  bool EInvaderGroup::areAllInvadersDead() const
  {
    for (int i = 0; i < GameConfig::InvaderTotalCount; i++)
    {
      if (m_invaders[i]->isAlive())
      {
        return false;
      }
    }
    return true;
  }

  void EInvaderGroup::increaseInvaderVelocity()
  {
    m_currentInvaderVelocity += GameConfig::InvaderVelocityIncrease;
    for (int i = 0; i < GameConfig::InvaderTotalCount; i++)
    {
      m_invaders[i]->setVelocity(Vector2f(m_currentInvaderVelocity, 0.f));
    }
  }

  EInvaderGroup::EInvaderGroup(const shared_ptr<Texture> spriteSheet, const Vector2f upperLeftStartPos) : 
    m_spriteSheet{ spriteSheet }, 
    m_timeLeftInAnimationFrame{ GameConfig::InvaderAnimFrameLength }, 
    m_upperLeftStartPos(upperLeftStartPos), 
    m_changeDirectionCooldown{ ChangeDirectionCooldownLength },
    m_currentInvaderVelocity { GameConfig::InvaderStartingVelocity }
  {
    const shared_ptr<CreateEntityWithSpritesheetData> spriteSheetDataPtr = std::make_shared<CreateEntityWithSpritesheetData>(m_spriteSheet);

    for (int y = GameConfig::InvaderRows-1; y >= 0; y--)
    {
      for (int x = 0; x < GameConfig::InvaderColumns; x++)
      {
        const int currIndex = y * GameConfig::InvaderColumns + x;
        const EntityType type = getInvaderType(y);
        shared_ptr<EInvader> currInvader = std::dynamic_pointer_cast<EInvader>(Engine::EntityFactoryInstance->createEntity(type, spriteSheetDataPtr));
        currInvader->setPosition(getInvaderStartPosition(type, y, x));
        currInvader->setDrawingCooldown(getDrawingCooldown(x, GameConfig::InvaderRows - 1 - y));
        m_invaders[currIndex] = currInvader;
      }
    }
  }

  bool EInvaderGroup::isAnimationFrameChangeNeeded(const float& deltaTime)
  {
    m_timeLeftInAnimationFrame -= deltaTime;
    const bool changeAnimFrame = m_timeLeftInAnimationFrame <= 0.f;
    if (changeAnimFrame)
    {
      m_timeLeftInAnimationFrame = GameConfig::InvaderAnimFrameLength;
    }
    return changeAnimFrame;
  }

  const EInvader* EInvaderGroup::getFirstAliveInvaderFromTheLeft() const
  {
    for (int x = 0; x < GameConfig::InvaderColumns; x++)
    {
      for (int y = 0; y < GameConfig::InvaderRows; y++)
      {
        shared_ptr<EInvader> currInv = getInvader(x, y);
        if (currInv->isAlive())
        {
          return currInv.get();
        }
      }
    }

    return nullptr;
  }

  const EInvader* EInvaderGroup::getFirstAliveInvaderFromTheRight() const
  {
    for (int x = GameConfig::InvaderColumns-1; x >= 0; x--)
    {
      for (int y = 0; y < GameConfig::InvaderRows; y++)
      {
        shared_ptr<EInvader> currInv = getInvader(x, y);
        if (currInv->isAlive())
        {
          return currInv.get();
        }
      }
    }
    return nullptr;
  }

  bool EInvaderGroup::isChangeDirectionNeeded(const float& deltaTime)
  {
    const EInvader* mostLeftInvader = getFirstAliveInvaderFromTheLeft();
    const EInvader* mostRightInvader = getFirstAliveInvaderFromTheRight();

    assert(mostLeftInvader != nullptr);
    assert(mostRightInvader != nullptr);

    const bool changeDirection = m_changeDirectionCooldown <= 0 && (mostLeftInvader->getPosition().x <= GameConfig::InvaderGroupLeftWall || mostRightInvader->getPosition().x + mostRightInvader->getRect().getWidth() >= GameConfig::InvaderGroupRightWall);

    if (changeDirection)
    {
      m_changeDirectionCooldown = ChangeDirectionCooldownLength;
    }
    if (m_changeDirectionCooldown > 0)
    {
      m_changeDirectionCooldown -= deltaTime;
    }

    return changeDirection;
  }

  shared_ptr<EInvader> EInvaderGroup::getInvader(const int column, const int row) const
  {
    return m_invaders[row * GameConfig::InvaderColumns + column];
  }

  EntityType EInvaderGroup::getInvaderType(const int row)
  {
    EntityType type = EntityType::SmallInvader;
    if (row > 1 && row < 3)
    {
      type = EntityType::MediumInvader;
    }
    else if (row >= 3)
    {
      type = EntityType::LargeInvader;
    }
    return type;
  }

  Vector2f EInvaderGroup::centerOffset(const EntityType type, Vector2f posOffset)
  {
    if (type == EntityType::SmallInvader)
    {
      posOffset += Vector2f((GameConfig::InvaderLargeSize.x - GameConfig::InvaderSmallSize.x) / 2.f, 0.f);
    }
    else if (type == EntityType::MediumInvader)
    {
      posOffset += Vector2f((GameConfig::InvaderLargeSize.x - GameConfig::InvaderMediumSize.x) / 2.f, 0.f);
    }
    return posOffset;
  }

  Vector2f EInvaderGroup::getInvaderStartPosition(const EntityType type, const int row, const int column) const
  {
    Vector2f posOffset = Vector2f(column*GameConfig::InvaderHorisontalSpacing, row*GameConfig::InvaderVerticalSpacing);
    posOffset = centerOffset(type, posOffset);
    return Vector2f(m_upperLeftStartPos.x, m_upperLeftStartPos.y) + posOffset;
  }
}

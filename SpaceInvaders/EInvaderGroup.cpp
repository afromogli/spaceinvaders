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

  EInvaderGroup::EInvaderGroup(const shared_ptr<Texture> spriteSheet, const Vector2f upperLeftStartPos) : 
    m_spriteSheet{ spriteSheet }, 
    m_timeLeftInAnimationFrame{ GameConfig::InvaderAnimFrameLength }, 
    m_changeDirectionCooldown{ ChangeDirectionCooldownLength }
  {
    const auto spriteSheetDataPtr = std::make_shared<CreateEntityWithSpritesheetData>(m_spriteSheet);

    for (int y = 0; y < GameConfig::InvaderRows; y++)
    {
      for (int x = 0; x < GameConfig::InvaderColumns; x++)
      {
        const int currIndex = y * GameConfig::InvaderColumns + x;
        const EntityType type = getInvaderType(y);
        Vector2f posOffset = Vector2f(x*GameConfig::InvaderHorisontalSpacing, y*GameConfig::InvaderVerticalSpacing);
        centerOffset(type, posOffset);        
        m_invaders[currIndex] = std::dynamic_pointer_cast<EInvader>(Engine::EntityFactoryInstance->createEntity(type, spriteSheetDataPtr));
        m_invaders[currIndex]->setPosition(Vector2f(upperLeftStartPos.x, upperLeftStartPos.y) + posOffset);
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

  bool EInvaderGroup::isChangeDirectionNeeded(const float& deltaTime)
  {
    const shared_ptr<EInvader> bottomLeftInvader = m_invaders[(GameConfig::InvaderRows - 1) * GameConfig::InvaderColumns];
    const shared_ptr<EInvader> bottomRightInvader = m_invaders[(GameConfig::InvaderRows - 1) * GameConfig::InvaderColumns + GameConfig::InvaderColumns - 1];

    const bool changeDirection = m_changeDirectionCooldown <= 0 &&
      (bottomLeftInvader->getPosition().x <= GameConfig::InvaderGroupLeftWall || bottomRightInvader->getPosition().x + bottomRightInvader->getRect().getWidth() >= GameConfig::InvaderGroupRightWall);

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

  void EInvaderGroup::centerOffset(const EntityType type, Vector2f& posOffset)
  {
    if (type == EntityType::SmallInvader)
    {
      posOffset += Vector2f((GameConfig::InvaderLargeSize.x - GameConfig::InvaderSmallSize.x) / 2.f, 0.f);
    }
    else if (type == EntityType::MediumInvader)
    {
      posOffset += Vector2f((GameConfig::InvaderLargeSize.x - GameConfig::InvaderMediumSize.x) / 2.f, 0.f);
    }
  }  
}

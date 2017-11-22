#include "EInvaderGroup.h"
#include "Engine.h"
#include <iostream>

using namespace Common;

namespace SpaceInvaders
{
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
        EntityType type = EntityType::SmallInvader;
        if (y > 1 && y < 3)
        {
          type = EntityType::MediumInvader;
        }
        else if (y >= 3)
        {
          type = EntityType::LargeInvader;
        }

        const int currIndex = y* GameConfig::InvaderColumns + x;
        m_invaders[currIndex] = std::dynamic_pointer_cast<EInvader>(Engine::EntityFactoryInstance->createEntity(type, spriteSheetDataPtr));
        m_invaders[currIndex]->setPosition(Vector2f(upperLeftStartPos.x + x*GameConfig::InvaderHorisontalSpacing, upperLeftStartPos.y + y*GameConfig::InvaderVerticalSpacing));
      }
    }
  }

  void EInvaderGroup::update(const float& deltaTime)
  {
    m_timeLeftInAnimationFrame -= deltaTime;
    const bool changeAnimFrame = m_timeLeftInAnimationFrame <= 0.f;
    if (changeAnimFrame)
    {
      m_timeLeftInAnimationFrame = GameConfig::InvaderAnimFrameLength;
    }
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
}

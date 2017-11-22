#include "EInvaderGroup.h"
#include "Engine.h"

using namespace Common;

namespace SpaceInvaders
{
  EInvaderGroup::EInvaderGroup(const shared_ptr<Texture> spriteSheet, const Vector2f upperLeftStartPos) : m_spriteSheet{ spriteSheet }
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
    for (int i = 0; i < GameConfig::InvaderRows* GameConfig::InvaderColumns; i++)
    {
      m_invaders[i]->update(deltaTime);
    }
  }

  void EInvaderGroup::draw(Graphics& graphics)
  {
    for (int i = 0; i < GameConfig::InvaderRows* GameConfig::InvaderColumns; i++)
    {
      m_invaders[i]->draw(graphics);
    }
  }
}

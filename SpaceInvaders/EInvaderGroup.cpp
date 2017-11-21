#include "EInvaderGroup.h"
#include "Engine.h"
#include <iostream>

using namespace Common;

namespace SpaceInvaders
{
  EInvaderGroup::EInvaderGroup(const shared_ptr<Texture> spriteSheet) : m_spriteSheet{ spriteSheet }
  {
    const auto spriteSheetDataPtr = std::make_shared<CreateEntityWithSpritesheetData>(m_spriteSheet);

    for (int y = 0; y < Rows; y++)
    {
      for (int x = 0; x < Columns; x++)
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

        const int currIndex = y*Columns + x;
        m_invaders[currIndex] = std::dynamic_pointer_cast<EInvader>(Engine::EntityFactoryInstance->createEntity(type, spriteSheetDataPtr));
        m_invaders[currIndex]->setPosition(Vector2f(x*GameConfig::InvaderHorisontalSpacing, y*GameConfig::InvaderVerticalSpacing));
      }
    }
  }

  void EInvaderGroup::update(const float& deltaTime)
  {
    for (int i = 0; i < Rows*Columns; i++)
    {
      m_invaders[i]->update(deltaTime);
    }
  }

  void EInvaderGroup::draw(Graphics& graphics)
  {
    for (int i = 0; i < Rows*Columns; i++)
    {
      m_invaders[i]->draw(graphics);
    }
  }
}

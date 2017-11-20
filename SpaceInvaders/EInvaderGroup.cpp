#include "EInvaderGroup.h"
#include "Engine.h"

using namespace Common;

namespace SpaceInvaders
{
  EInvaderGroup::EInvaderGroup(const shared_ptr<Texture> spriteSheet)
  {
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

        m_invaders[y*Columns + x] = std::dynamic_pointer_cast<EInvader>(Engine::EntityFactoryInstance->createEntity(type, spriteSheet.get()));
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

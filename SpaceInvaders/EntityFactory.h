#pragma once

#include <memory>
#include "Graphics.h"
#include "Entity.h"
#include "EntityType.h"

namespace Common {
  class Texture;
}

using namespace std;
using namespace Common;

namespace SpaceInvaders
{
  class EntityFactory
  {
  public:
    EntityFactory(Graphics& graphics) : m_graphics{ graphics }
    {
    }
    
    /**
     * @brief Creates an entity of the specified type
     * @param type The entity type
     * @param data Any necessary data to be used when constructing the entity
     * @returns The created entity
     */
    shared_ptr<Entity> createEntity(const EntityType &type, void* data=nullptr) const;

  private:
    static shared_ptr<Entity> createPaddleEntity(const Texture& spriteSheet);

    Graphics& m_graphics;
  };
}


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
  /**
   * @brief Extend this class to pass data for when creating the entity
   */
  class CreateEntityData
  {
  public:
    virtual ~CreateEntityData();
  };

  /**
   * @brief Used for creating entity that needs spriteSheet
   */
  class CreateEntityWithSpritesheetData : public CreateEntityData
  {
  public:
    CreateEntityWithSpritesheetData(const shared_ptr<Texture> spriteSheet);
    const shared_ptr<Texture> SpriteSheet;
  };

  /**
  * @brief Used for creating invader group
  */
  class CreateInvaderGroupEntityData : public CreateEntityWithSpritesheetData
  {
  public:
    CreateInvaderGroupEntityData(const shared_ptr<Texture> spriteSheet, const Vector2f upperLeftStartPos);
    const Vector2f UpperLeftStartPos;
  };



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
    shared_ptr<Entity> createEntity(const EntityType type, const shared_ptr<CreateEntityData> data) const;

  private:
    static shared_ptr<Entity> createCannon(const shared_ptr<Texture> spriteSheet);
    static shared_ptr<Entity> createInvader(const EntityType type, const shared_ptr<Texture> spriteSheet);
    static shared_ptr<Entity> createInvaderGroup(const shared_ptr<Texture> spriteSheet, const Vector2f upperLeftStartPos);
    static shared_ptr<Entity> createHouse(const shared_ptr<Texture> spriteSheet);
    static shared_ptr<Entity> createCannonRocket();
    static shared_ptr<Entity> createInvaderRocket(const shared_ptr<Texture> spriteSheet);
    static shared_ptr<Entity> createLife(const shared_ptr<Texture> spriteSheet);
    static shared_ptr<Entity> createMysteryShip(const shared_ptr<Texture> spriteSheet);

    static void checkSpriteSheetDataPtr(const shared_ptr<CreateEntityWithSpritesheetData>& data);

    Graphics& m_graphics;
  };
}


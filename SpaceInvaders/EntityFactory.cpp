#include <string>

#include "NotSupportedException.h"
#include "EntityFactory.h"

#include "ECannon.h"
#include "EInvader.h"
#include "EInvaderGroup.h"
#include "InvalidCastException.h"

namespace SpaceInvaders
{
  CreateEntityData::~CreateEntityData()
  {
  }

  CreateEntityWithSpritesheetData::CreateEntityWithSpritesheetData(const shared_ptr<Texture> spriteSheet) : SpriteSheet{spriteSheet}
  {
  }

  CreateInvaderGroupEntityData::CreateInvaderGroupEntityData(const shared_ptr<Texture> spriteSheet, const Vector2f upperLeftStartPos) : 
    CreateEntityWithSpritesheetData(spriteSheet), UpperLeftStartPos{upperLeftStartPos}
  {
  }

  shared_ptr<Entity> EntityFactory::createEntity(const EntityType type, const shared_ptr<CreateEntityData> data) const
  {
    shared_ptr<Entity> entity;
    switch (type)
    {
    case EntityType::Cannon:
      entity = createCannonEntity(std::dynamic_pointer_cast<CreateEntityWithSpritesheetData>(data)->SpriteSheet);
      break;
    case EntityType::SmallInvader:
    case EntityType::MediumInvader:
    case EntityType::LargeInvader:
      entity = createInvaderEntity(type, std::dynamic_pointer_cast<CreateEntityWithSpritesheetData>(data)->SpriteSheet);
      break;
    case EntityType::InvaderGroup:
      {
        const shared_ptr<CreateInvaderGroupEntityData> invaderGroupData = std::dynamic_pointer_cast<CreateInvaderGroupEntityData>(data);
        if (invaderGroupData.use_count() == 0)
        {
          throw new InvalidCastException("Invalid CreateEntityData type provided");
        }
        entity = createInvaderGroup(invaderGroupData->SpriteSheet, invaderGroupData->UpperLeftStartPos);
        break;
      }      
    default:
      throw new NotSupportedException("The EntityType: " + std::to_string(type) + " is not supported");
    }
    return entity;
  }

  shared_ptr<Entity> EntityFactory::createCannonEntity(const shared_ptr<Texture> spriteSheet)
  {
    return shared_ptr<Entity>(new ECannon(spriteSheet));
  }

  shared_ptr<Entity> EntityFactory::createInvaderEntity(const EntityType type, const shared_ptr<Texture> spriteSheet)
  {
    return shared_ptr<Entity>(new EInvader(type, spriteSheet));
  }

  shared_ptr<Entity> EntityFactory::createInvaderGroup(const shared_ptr<Texture> spriteSheet, const Vector2f upperLeftStartPos)
  {
    return shared_ptr<Entity>(new EInvaderGroup(spriteSheet, upperLeftStartPos));
  }
}



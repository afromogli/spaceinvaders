#include <string>

#include "UnsupportedException.h"
#include "EntityFactory.h"

#include "ECannon.h"
#include "EInvader.h"
#include "EInvaderGroup.h"
#include "InvalidCastException.h"
#include "EBunker.h"
#include "ECannonRocket.h"
#include "EInvaderRocket.h"
#include "ELife.h"

namespace SpaceInvaders
{
  CreateEntityData::~CreateEntityData()
  {
  }


  CreateEntityWithSpritesheetData::CreateEntityWithSpritesheetData(const shared_ptr<Texture> spriteSheet) : SpriteSheet{ spriteSheet }
  {
  }


  CreateInvaderGroupEntityData::CreateInvaderGroupEntityData(const shared_ptr<Texture> spriteSheet, const Vector2f upperLeftStartPos) :
    CreateEntityWithSpritesheetData(spriteSheet), UpperLeftStartPos{ upperLeftStartPos }
  {
  }


  shared_ptr<Entity> EntityFactory::createEntity(const EntityType type, const shared_ptr<CreateEntityData> data) const
  {
    shared_ptr<Entity> entity;
    switch (type)
    {
    case EntityType::Cannon:
      entity = createCannon(std::dynamic_pointer_cast<CreateEntityWithSpritesheetData>(data)->SpriteSheet);
      break;
    case EntityType::SmallInvader:
    case EntityType::MediumInvader:
    case EntityType::LargeInvader:
    {
      const shared_ptr<CreateEntityWithSpritesheetData> spriteSheetData = dynamic_pointer_cast<CreateEntityWithSpritesheetData>(data);
      checkSpriteSheetDataPtr(spriteSheetData);
      entity = createInvader(type, std::dynamic_pointer_cast<CreateEntityWithSpritesheetData>(spriteSheetData)->SpriteSheet);
      break;
    }
    case EntityType::InvaderGroup:
    {
      const shared_ptr<CreateInvaderGroupEntityData> invaderGroupData = std::dynamic_pointer_cast<CreateInvaderGroupEntityData>(data);
      if (invaderGroupData.use_count() == 0)
      {
        throw new InvalidCastException(L"Invalid CreateEntityData type provided");
      }
      entity = createInvaderGroup(invaderGroupData->SpriteSheet, invaderGroupData->UpperLeftStartPos);
      break;
    }
    case EntityType::Bunker:
    {
      const shared_ptr<CreateEntityWithSpritesheetData> spriteSheetData = dynamic_pointer_cast<CreateEntityWithSpritesheetData>(data);
      checkSpriteSheetDataPtr(spriteSheetData);
      entity = createHouse(spriteSheetData->SpriteSheet);
      break;
    }
    case EntityType::CannonRocket:
    {
      entity = createCannonRocket();
      break;
    }
    case EntityType::InvaderRocket:
    {
      const shared_ptr<CreateEntityWithSpritesheetData> spriteSheetData = dynamic_pointer_cast<CreateEntityWithSpritesheetData>(data);
      checkSpriteSheetDataPtr(spriteSheetData);
      entity = createInvaderRocket(spriteSheetData->SpriteSheet);
      break;
    }
    case EntityType::Life:
    {
      const shared_ptr<CreateEntityWithSpritesheetData> spriteSheetData = dynamic_pointer_cast<CreateEntityWithSpritesheetData>(data);
      checkSpriteSheetDataPtr(spriteSheetData);
      entity = createLife(spriteSheetData->SpriteSheet);
      break;
    }
    default:
      throw new UnsupportedException(L"The EntityType: " + std::to_wstring(type) + L" is not supported");
    }
    return entity;
  }

  void EntityFactory::checkSpriteSheetDataPtr(const shared_ptr<CreateEntityWithSpritesheetData>& data)
  {
    if (data.use_count() == 0)
    {
      throw new InvalidCastException(L"Invalid CreateEntityData type provided");
    }
  }

  shared_ptr<Entity> EntityFactory::createCannon(const shared_ptr<Texture> spriteSheet)
  {
    return shared_ptr<Entity>(new ECannon(spriteSheet));
  }

  shared_ptr<Entity> EntityFactory::createInvader(const EntityType type, const shared_ptr<Texture> spriteSheet)
  {
    return shared_ptr<Entity>(new EInvader(type, spriteSheet));
  }

  shared_ptr<Entity> EntityFactory::createInvaderGroup(const shared_ptr<Texture> spriteSheet, const Vector2f upperLeftStartPos)
  {
    return shared_ptr<Entity>(new EInvaderGroup(spriteSheet, upperLeftStartPos));
  }

  shared_ptr<Entity> EntityFactory::createHouse(const shared_ptr<Texture> spriteSheet)
  {
    return shared_ptr<Entity>(new EBunker(spriteSheet));
  }

  shared_ptr<Entity> EntityFactory::createCannonRocket()
  {
    return shared_ptr<Entity>(new ECannonRocket());
  }

  shared_ptr<Entity> EntityFactory::createInvaderRocket(const shared_ptr<Texture> spriteSheet)
  {
    return shared_ptr<Entity>(new EInvaderRocket(spriteSheet));
  }

  shared_ptr<Entity> EntityFactory::createLife(const shared_ptr<Texture> spriteSheet)
  {
    return shared_ptr<Entity>(new ELife(spriteSheet));
  }
}



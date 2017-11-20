#include <string>

#include "NotSupportedException.h"
#include "EntityFactory.h"

#include "ECannon.h"

namespace SpaceInvaders
{
   shared_ptr<Entity> EntityFactory::createEntity(const EntityType& type, void* data) const
   {
      shared_ptr<Entity> entity = nullptr;
      switch (type)
      {
      case EntityType::Cannon:
         entity = this->createCannonEntity(*static_cast<Texture*>(data));
         break;
      default:
         throw new NotSupportedException("The EntityType: " + std::to_string(type) + " is not supported");
      }
      return entity;
   }

   shared_ptr<Entity> EntityFactory::createCannonEntity(const Texture& spriteSheet)
   {
      return shared_ptr<Entity>(new ECannon(spriteSheet));
   }
}



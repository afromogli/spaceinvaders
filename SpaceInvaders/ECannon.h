#pragma once

#include "Entity.h"
#include <memory>
//#include "EBall.h"

using namespace std;
using namespace Common;

namespace SpaceInvaders 
{
   class EntityFactory;

   class ECannon : public Entity {
      friend class EntityFactory;
   public:
      void update(const float& deltaTime) override;
      void draw(Graphics& graphics) override;
  /*    bool isColliding(const EBall& ball) const;
      void doBallCollision(EBall& ball) const;*/
   private:
      ECannon();

   };
}


#pragma once

#include "Entity.h"
#include "Texture.h"
#include "EntityType.h"

using namespace std;
using namespace Common;

namespace SpaceInvaders
{
  class EntityFactory;

  class EInvader : public Entity {
    friend class EntityFactory;
  public:
    void update(const float& deltaTime) override;
    void draw(Graphics& graphics) override;
    void changeDirection();

    static Rect2D SmallInvaderClip;// = Rect2D(Vector2f(0, 0), 0, 0);
    static Rect2D MediumInvaderClip;// = Rect2D(Vector2f(0, 0), 0, 0);
    static Rect2D LargeInvaderClip;// = Rect2D(Vector2f(0, 0), 0, 0);
  private:
    EInvader(EntityType invaderType, Graphics& graphics);
    Texture m_texture;
    EntityType m_invaderType;    
  };
}

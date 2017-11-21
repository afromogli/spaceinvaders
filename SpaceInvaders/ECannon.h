#pragma once

#include "Entity.h"
#include "Texture.h"
#include <memory>

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

    static Rect2D CannonClip;

  private:
    ECannon(const shared_ptr<Texture> spriteSheet);
    const shared_ptr<Texture> m_spriteSheet;
  };
}


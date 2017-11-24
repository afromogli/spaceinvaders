#pragma once
#include "Entity.h"
#include "Texture.h"
#include <memory>

using namespace Common;

namespace SpaceInvaders
{
  class ECannonRocket : public Entity
  {
    friend class EntityFactory;
  public:
    void update(const float& deltaTime) override;
    void draw(Graphics& graphics) override;
  private:
    ECannonRocket(/*const shared_ptr<Texture> spriteSheet*/);

    //const shared_ptr<Texture> m_spriteSheet;
  };
}

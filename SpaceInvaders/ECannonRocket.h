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

    bool isAlive() const;
    void setIsAlive(bool isAlive);
  private:
    ECannonRocket(/*const shared_ptr<Texture> spriteSheet*/);
    
    bool m_isAlive;
    //const shared_ptr<Texture> m_spriteSheet;
  };
}

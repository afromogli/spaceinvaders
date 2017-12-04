#pragma once
#include "Entity.h"
#include "Texture.h"

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

  protected:
    virtual bool isOutOfView() const;

    ECannonRocket();
    
    bool m_isAlive;
  };
}

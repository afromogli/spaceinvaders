#pragma once

#include <memory>

#include "Entity.h"
#include "EInvader.h"

using namespace Common;

namespace SpaceInvaders
{
  class EInvaderGroup : public Entity
  {
    friend class EntityFactory;
  public:
    
    void update(const float& deltaTime) override;
    void draw(Graphics& graphics) override;


    static constexpr int Rows = 5;
    static constexpr int Columns = 11;

  private:
    explicit EInvaderGroup(const shared_ptr<Texture> spriteSheet);

    shared_ptr<EInvader> m_invaders[Rows*Columns];

    const shared_ptr<Texture> m_spriteSheet;
  };
}
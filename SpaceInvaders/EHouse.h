#pragma once

#include "Entity.h"
#include "GameConfig.h"
#include <memory>
#include "Texture.h"

using namespace Common;

namespace SpaceInvaders
{
  /**
   * @brief The house acts as protection for player and is destroyed if hit by to many rockets.
   */
  class EHouse : public Entity
  {
    friend class EntityFactory;
  public:
    void update(const float& deltaTime) override;
    void draw(Graphics& graphics) override;

  private:
    EHouse(const shared_ptr<Texture> spriteSheet);

    static constexpr Vector2f HouseSpriteSize = Vector2f(44.f, 33.f);
    static Rect2D HouseAnimClipFrames[GameConfig::HouseAnimFramesCount];

    float m_health;
    const shared_ptr<Texture> m_spriteSheet;
  };
}
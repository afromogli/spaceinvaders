#pragma once

#include "Entity.h"
#include "Texture.h"
#include "EntityType.h"
#include "GameConfig.h"
#include <memory>

using namespace std;
using namespace Common;

namespace SpaceInvaders
{
  class EntityFactory;

  class EInvader : public Entity
  {
    friend class EntityFactory;
  public:
    void update(const float& deltaTime) override;
    void draw(Graphics& graphics) override;
    void changeDirection();
    void changeAnimationFrame();

    static Rect2D SmallInvaderClipFrames[GameConfig::InvaderAnimFramesCount];
    static Rect2D MediumInvaderClipFrames[GameConfig::InvaderAnimFramesCount];
    static Rect2D LargeInvaderClipFrames[GameConfig::InvaderAnimFramesCount];

  private:
    EInvader(EntityType invaderType, const shared_ptr<Texture> spriteSheet);
    const shared_ptr<Texture> m_spriteSheet;
    EntityType m_invaderType;
    int m_currentFrame; // Is either 0 or 1
  };
}

#pragma once

#include "Vector2.h"

using namespace Common;

namespace SpaceInvaders
{
  class GameConfig
  {
  public:
    // Engine and window configuration
    static constexpr float MsPerUpdate = 4.0f;
    static constexpr Vector2f WinInitPos = Vector2f(300.f, 300.f);
    static constexpr Vector2f WinSize = Vector2f(1024.f, 768.f);

    // Main scene configuration
    static constexpr Vector2f CannonSize = Vector2f(60.f, 30.f);
    static constexpr Vector2f InitialCannonPosition = Vector2f(GameConfig::WinSize.x / 2, GameConfig::WinSize.y - (CannonSize.y + 10));
    static constexpr float CannonSpeed = 400.0f; // Pixels per second;
    
    static constexpr Vector2f InvaderLeftVelocity = Vector2f(-1.f, 0.f);
    static constexpr Vector2f InvaderRightVelocity = Vector2f(1.f, 0.f);

    static constexpr uint8_t InvaderAnimFramesCount = 2;

  private:
    GameConfig() {}
  };
}

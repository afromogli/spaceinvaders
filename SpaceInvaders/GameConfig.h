#pragma once

#include "Vector2.h"

using namespace Common;

namespace SpaceInvaders
{
  class GameConfig
  {
  public:
    // Engine and window configuration
    static constexpr float MsPerUpdate = 4.f;
    static constexpr Vector2f WinInitPos = Vector2f(300.f, 300.f);
    static constexpr Vector2f WinSize = Vector2f(1024.f, 768.f);

    // Graphics configuration
    static constexpr float SpriteScale = 2.f;

    // Cannon
    static constexpr Vector2f CannonSize = Vector2f(26.f * SpriteScale, 16.f * SpriteScale);
    static constexpr Vector2f InitialCannonPosition = Vector2f(GameConfig::WinSize.x / 2, GameConfig::WinSize.y - (CannonSize.y + 10));
    static constexpr float CannonSpeed = 400.0f; // Pixels per second;

    // Invader
    static constexpr float InvaderVelocity = 30.f;
    static constexpr Vector2f InvaderSmallSize = Vector2f(16.f * SpriteScale, 16.f * SpriteScale);
    static constexpr Vector2f InvaderMediumSize = Vector2f(22.f * SpriteScale, 16.f * SpriteScale);
    static constexpr Vector2f InvaderLargeSize = Vector2f(24.f * SpriteScale, 16.f * SpriteScale);
    static constexpr Vector2f InvaderLeftVelocity = Vector2f(-1.f*InvaderVelocity, 0.f);
    static constexpr Vector2f InvaderRightVelocity = Vector2f(InvaderVelocity, 0.f);
    static constexpr uint8_t InvaderAnimFramesCount = 2;
    static constexpr float InvaderAnimFrameLength = 500.f; // millisecs
    
    // Invader group
    static constexpr Vector2f InvaderGroupStartPos = Vector2f(50.f, 50.f);
    static constexpr float InvaderHorisontalSpacing = InvaderLargeSize.x + 5.f;
    static constexpr float InvaderVerticalSpacing = InvaderLargeSize.y + 5.f;

    static constexpr int InvaderRows = 5;
    static constexpr int InvaderColumns = 11;
    static constexpr int InvaderTotalCount = InvaderRows*InvaderColumns;

    static constexpr float InvaderGroupWallPadding = 10.f;
    static constexpr float InvaderGroupLeftWall = 0.f + InvaderGroupWallPadding;
    static constexpr float InvaderGroupRightWall = WinSize.x- InvaderGroupWallPadding;

    static constexpr float InvaderGroupMoveDownDistance = InvaderSmallSize.y;

  private:
    GameConfig() {}
  };
}

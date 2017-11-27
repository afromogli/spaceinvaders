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

    // Scores
    static constexpr int SmallInvaderScore = 40;
    static constexpr int MediumInvaderScore = 20;
    static constexpr int LargeInvaderScore = 10;
    static constexpr int MothershipInvaderScore = 0; // TODO: find out what the secret score is

    // Cannon
    static constexpr Vector2f CannonSize = Vector2f(26.f, 16.f) * SpriteScale;
    static constexpr Vector2f InitialCannonPosition = Vector2f(GameConfig::WinSize.x / 2, GameConfig::WinSize.y - (CannonSize.y + 10));
    static constexpr float CannonSpeed = 400.0f; // Px per sec

    // Cannon rocket
    static constexpr Vector2f CannonRocketVelocity = Vector2f(0.f, -800.f); // Px per sec
    static constexpr Vector2f CannonRocketSize = Vector2f(2.f, 10.f);

    // House
    static constexpr int HouseAnimFramesCount = 5;
    static constexpr float HouseMaxHealth = 10.f;
    static constexpr float HouseCannonRocketDamage = 1.f;
    static constexpr Vector2f HouseSize = Vector2f(44.f, 33.f) * SpriteScale;
    static constexpr Vector2f HouseVerticalOffset = Vector2f(0, WinSize.y - 130.f);

    // Invader
    static constexpr float InvaderVelocity = 30.f;
    static constexpr Vector2f InvaderSmallSize =  Vector2f(16.f, 16.f) * SpriteScale;
    static constexpr Vector2f InvaderMediumSize = Vector2f(22.f, 16.f) * SpriteScale;
    static constexpr Vector2f InvaderLargeSize = Vector2f(24.f, 16.f ) * SpriteScale;
    static constexpr Vector2f InvaderLeftVelocity = Vector2f(-1.f*InvaderVelocity, 0.f);
    static constexpr Vector2f InvaderRightVelocity = Vector2f(InvaderVelocity, 0.f);
    static constexpr uint8_t InvaderAnimFramesCount = 2;
    static constexpr float InvaderAnimFrameLength = 500.f; // ms
    
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
    
    // Invader rocket
    static constexpr Vector2f InvaderRocketSize = Vector2f(6.f, 12.f) * SpriteScale;
    static constexpr Vector2f InvaderRocketVelocity = Vector2f(0.f, 300.f); // Px per sec
    static constexpr int InvaderRocketsMaxCount = InvaderRows*InvaderColumns / 2;
    static constexpr float InvaderRocketSpawnMaxCooldown = 3000.f;

  private:
    GameConfig() {}
  };
}

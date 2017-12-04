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

    // Resource paths
    static constexpr wchar_t* GamesFontPath = L"Fonts\\Games.ttf";

    // Scores and lives
    static constexpr int SmallInvaderScore = 30;
    static constexpr int MediumInvaderScore = 20;
    static constexpr int LargeInvaderScore = 10;
    static constexpr int MysteryShipMaxScore = 300;
    static constexpr int LivesMax = 3;

    // Cannon (player)
    static constexpr Vector2f CannonSize = Vector2f(26.f, 16.f) * SpriteScale;
    static constexpr Vector2f InitialCannonPosition = Vector2f(GameConfig::WinSize.x / 2, GameConfig::WinSize.y - (CannonSize.y + 10));
    static constexpr float CannonSpeed = 400.0f; // Px per sec

    // Cannon rocket
    static constexpr Vector2f CannonRocketVelocity = Vector2f(0.f, -800.f); // Px per sec
    static constexpr Vector2f CannonRocketSize = Vector2f(2.f, 10.f);

    // Bunker
    static constexpr int BunkerAnimFramesCount = 5;
    static constexpr float BunkerMaxHealth = 10.f;
    static constexpr float BunkerCannonRocketDamage = 1.f;
    static constexpr Vector2f BunkerSize = Vector2f(44.f, 33.f) * SpriteScale;
    static constexpr Vector2f BunkerVerticalOffset = Vector2f(0, WinSize.y - 130.f);

    // Invader
    static constexpr float InvaderStartingVelocity = 30.f;
    static constexpr float InvaderVelocityIncrease = 0.75f * InvaderStartingVelocity;
    static constexpr Vector2f InvaderSmallSize =  Vector2f(16.f, 16.f) * SpriteScale;
    static constexpr Vector2f InvaderMediumSize = Vector2f(22.f, 16.f) * SpriteScale;
    static constexpr Vector2f InvaderLargeSize = Vector2f(24.f, 16.f ) * SpriteScale;
    static constexpr uint8_t InvaderAnimFramesCount = 2;
    static constexpr float InvaderAnimFrameLength = 500.f; // ms
    static constexpr float InvaderDrawingCooldown = 10.f;

    // Invader group
    static constexpr Vector2f InvaderGroupStartPos = Vector2f(50.f, 50.f);
    static constexpr float InvaderHorisontalSpacing = InvaderLargeSize.x + 20.f;
    static constexpr float InvaderVerticalSpacing = InvaderLargeSize.y + 10.f;

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

#include "EHouse.h"

namespace SpaceInvaders
{
  void EHouse::update(const float& deltaTime)
  {
  }

  void EHouse::draw(Graphics& graphics)
  {
    // TODO: pick correct frame based on health
    const Rect2D& clip = HouseAnimClipFrames[0];
    m_spriteSheet->render(getPosition(), clip, GameConfig::SpriteScale);
  }

  Rect2D EHouse::HouseAnimClipFrames[GameConfig::HouseAnimFramesCount] = {
    Rect2D(Vector2f(316.f, 5.f), int(HouseSpriteSize.x), int(HouseSpriteSize.y)),
    Rect2D(Vector2f(480.f, 3.f), int(HouseSpriteSize.x), int(HouseSpriteSize.y)),
    Rect2D(Vector2f(480.f, 58.f), int(HouseSpriteSize.x), int(HouseSpriteSize.y)),
    Rect2D(Vector2f(373.f, 4.f), int(HouseSpriteSize.x), int(HouseSpriteSize.y)),
    Rect2D(Vector2f(428.f, 3.f), int(HouseSpriteSize.x), int(HouseSpriteSize.y))
  };

  EHouse::EHouse(const shared_ptr<Texture> spriteSheet) : m_health{GameConfig::HouseMaxHealth}, m_spriteSheet {spriteSheet}
  {
    m_rect.setSize(GameConfig::HouseSize);
  }
}

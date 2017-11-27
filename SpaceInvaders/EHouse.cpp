#include "EHouse.h"

namespace SpaceInvaders
{
  void EHouse::update(const float& deltaTime)
  {
  }

  void EHouse::draw(Graphics& graphics)
  {
    if (m_isAlive)
    {
      // TODO: fix better house damaga gfx, looks like crap right now
      const Rect2D& clip = HouseAnimClipFrames[int((1.f - m_health / GameConfig::HouseMaxHealth) * GameConfig::HouseAnimFramesCount)];
      m_spriteSheet->render(getPosition(), clip, GameConfig::SpriteScale);
    }
  }

  bool EHouse::isColliding(const ECannonRocket& rocket) const
  {
    return m_rect.intersects(rocket.getRect());
  }

  void EHouse::decreaseHealth()
  {
    m_health -= GameConfig::HouseCannonRocketDamage;
    m_isAlive = m_health > 0.f;
  }

  void EHouse::setIsAlive(const bool isAlive)
  {
    m_isAlive = isAlive;
  }

  bool EHouse::isAlive() const
  {
    return m_isAlive;
  }

  Rect2D EHouse::HouseAnimClipFrames[GameConfig::HouseAnimFramesCount] = {
    Rect2D(Vector2f(316.f, 5.f), int(HouseSpriteSize.x), int(HouseSpriteSize.y)),
    Rect2D(Vector2f(480.f, 3.f), int(HouseSpriteSize.x), int(HouseSpriteSize.y)),
    Rect2D(Vector2f(480.f, 58.f), int(HouseSpriteSize.x), int(HouseSpriteSize.y)),
    Rect2D(Vector2f(373.f, 4.f), int(HouseSpriteSize.x), int(HouseSpriteSize.y)),
    Rect2D(Vector2f(428.f, 3.f), int(HouseSpriteSize.x), int(HouseSpriteSize.y))
  };

  EHouse::EHouse(const shared_ptr<Texture> spriteSheet) : 
    m_health { GameConfig::HouseMaxHealth }, 
    m_spriteSheet { spriteSheet }, 
    m_isAlive { true }
  {
    m_rect.setSize(GameConfig::HouseSize);
  }
}

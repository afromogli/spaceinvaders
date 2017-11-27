#include "GameConfig.h"
#include "EInvaderRocket.h"

namespace SpaceInvaders
{
  void EInvaderRocket::draw(Graphics& graphics)
  {
    if (isAlive())
    {
      m_spriteSheet->render(getPosition(), InvaderRocketClip, GameConfig::SpriteScale);
    }
  }

  EInvaderRocket::EInvaderRocket(const shared_ptr<Texture> spriteSheet) : m_spriteSheet {spriteSheet}
  {
    m_rect.setSize(GameConfig::InvaderRocketSize);
    setVelocity(GameConfig::InvaderRocketVelocity);
  }

  bool EInvaderRocket::isOutOfView() const
  {
    return getPosition().y > GameConfig::WinSize.y;
  }

  Rect2D EInvaderRocket::InvaderRocketClip = Rect2D(Vector2f(413.f, 70.f), 6, 12);
}



#include "EMysteryShip.h"

namespace SpaceInvaders
{
  void EMysteryShip::draw(Graphics& graphics)
  {
    if (isAlive())
    {
      m_spriteSheet->render(getPosition(), MysterShipClip, GameConfig::SpriteScale);
    }
  }

  EMysteryShip::EMysteryShip(const shared_ptr<Texture> spriteSheet) : EInvader(EntityType::MysteryShip, spriteSheet)
  {
    m_drawingCooldown = 0;
  }

  Rect2D EMysteryShip::MysterShipClip = Rect2D(Vector2f(215.f, 17.f), 48, 21);
}

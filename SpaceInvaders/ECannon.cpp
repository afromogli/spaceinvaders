#include "ECannon.h"
#include "GameConfig.h"


namespace SpaceInvaders
{
  ECannon::ECannon(const shared_ptr<Texture> spriteSheet) : Entity(), m_spriteSheet{ spriteSheet }
  {
    m_rect.setSize(int(GameConfig::CannonSize.x), int(GameConfig::CannonSize.y));
  }

  void ECannon::update(const float & deltaTime)
  {
    const float deltaSeconds = deltaTime / 1000;
    const Vector2f nextPosition = getPosition() + m_velocity*deltaSeconds;
    if ((nextPosition.y) > 0 && (nextPosition.y + m_rect.getHeight()) < GameConfig::WinSize.y) {
      setPosition(nextPosition);
    }
  }

  void ECannon::draw(Graphics& graphics)
  {
    m_spriteSheet->render(getPosition(), CannonClip, GameConfig::SpriteScale);
  }

  Rect2D ECannon::CannonClip = Rect2D(Vector2f(277, 21), 26, 16);
}
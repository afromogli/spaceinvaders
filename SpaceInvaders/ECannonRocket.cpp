#include "ECannonRocket.h"
#include "GameConfig.h"

namespace SpaceInvaders
{
  void ECannonRocket::update(const float& deltaTime)
  {
    setPosition(getPosition() + GameConfig::CannonRocketVelocity*deltaTime);
  }

  void ECannonRocket::draw(Graphics& graphics)
  {
    graphics.drawFilledBox(m_rect, Colors::White);
  }

  ECannonRocket::ECannonRocket()
  {
    m_rect.setSize(GameConfig::CannonRocketSize);
  }
}



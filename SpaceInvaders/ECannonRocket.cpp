#include "ECannonRocket.h"
#include "GameConfig.h"

namespace SpaceInvaders
{
  void ECannonRocket::update(const float& deltaTime)
  {
    if (isAlive())
    {
      // check if rocket is out of screen
      if (getPosition().y < 0.f)
      {
        setIsAlive(false);
      }

      const float deltaSeconds = deltaTime / 1000;
      setPosition(getPosition() + GameConfig::CannonRocketVelocity*deltaSeconds);
    }    
  }

  void ECannonRocket::draw(Graphics& graphics)
  {
    if (isAlive())
    {
      graphics.drawFilledBox(m_rect, Colors::White);
    }
  }

  bool ECannonRocket::isAlive() const
  {
    return m_isAlive;
  }

  void ECannonRocket::setIsAlive(const bool isAlive)
  {
    m_isAlive = isAlive;
  }

  ECannonRocket::ECannonRocket() : m_isAlive { false }
  {
    m_rect.setSize(GameConfig::CannonRocketSize);
  }
}



#include "ECannonRocket.h"
#include "GameConfig.h"

namespace SpaceInvaders
{
  void ECannonRocket::update(const float& deltaTime)
  {
    if (isAlive())
    {
      if (isOutOfView())
      {
        setIsAlive(false);
      }
      const float deltaSeconds = deltaTime / 1000;
      setPosition(getPosition() + getVelocity()*deltaSeconds);
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

  bool ECannonRocket::isOutOfView() const
  {
    return getPosition().y < 0.f;
  }

  ECannonRocket::ECannonRocket() : m_isAlive { false }
  {
    m_rect.setSize(GameConfig::CannonRocketSize);
    setVelocity(GameConfig::CannonRocketVelocity);
  }
}



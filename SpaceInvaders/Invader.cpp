#include "Invader.h"
#include "GameConfig.h"
#include <cassert>

namespace SpaceInvaders
{
  EInvader::EInvader(const EntityType invaderType, Graphics& graphics) : m_texture {graphics}
  {
    m_rect.setSize(int(GameConfig::CannonSize.x), int(GameConfig::CannonSize.y));
    m_velocity = GameConfig::InvaderRightVelocity; // Initial speed
    m_invaderType = invaderType;
    //m_texture.loadFromFile()
  }

  void EInvader::update(const float & deltaTime)
  {
    const float deltaSeconds = deltaTime / 1000; // ms -> s conversion
    const Vector2f nextPosition = getPosition() + m_velocity*deltaSeconds;
    assert(nextPosition.x >= 0 && nextPosition.x + m_rect.getWidth() < GameConfig::WinSize.y);
    setPosition(nextPosition);
  }

  void EInvader::draw(Graphics & graphics)
  {
    graphics.drawFilledBox(m_rect, Colors::White);
  }

  void EInvader::changeDirection()
  {
    if (m_velocity == GameConfig::InvaderLeftVelocity)
    {
      m_velocity = GameConfig::InvaderRightVelocity;
    }
    else
    {
      m_velocity = GameConfig::InvaderLeftVelocity;
    }
  }
}

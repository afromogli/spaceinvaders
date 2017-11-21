#include <cassert>

#include "EInvader.h"
#include "GameConfig.h"
#include "NotSupportedException.h"

namespace SpaceInvaders
{
  EInvader::EInvader(const EntityType invaderType, const shared_ptr<Texture> spriteSheet) : m_spriteSheet{ spriteSheet }
  {
    m_rect.setSize(int(GameConfig::CannonSize.x), int(GameConfig::CannonSize.y));
    m_velocity = GameConfig::InvaderRightVelocity; // Initial speed
    m_invaderType = invaderType;
    m_currentFrame = 0;
    assert(spriteSheet->isLoaded());
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
    Rect2D *clip = nullptr;

    switch (m_invaderType)
    {
    case EntityType::SmallInvader:
      clip = &SmallInvaderClipFrames[m_currentFrame];
      break;
    case EntityType::MediumInvader:
      clip = &MediumInvaderClipFrames[m_currentFrame];
      break;
    case EntityType::LargeInvader:
      clip = &LargeInvaderClipFrames[m_currentFrame];
      break;
    default:
      throw new NotSupportedException("The invader type: " + std::to_string(m_invaderType) + " is not supported.");
    }

    m_spriteSheet->render(getPosition(), *clip);
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

  void EInvader::changeAnimationFrame()
  {
    m_currentFrame = ++m_currentFrame % GameConfig::InvaderAnimFramesCount;
  }

  Rect2D EInvader::SmallInvaderClipFrames[GameConfig::InvaderAnimFramesCount] = { Rect2D(Vector2f(7.f, 18.f), 16, 16), Rect2D(Vector2f(40.f, 18.f), 16, 16) };
  Rect2D EInvader::MediumInvaderClipFrames[GameConfig::InvaderAnimFramesCount] = { Rect2D(Vector2f(74.f, 18.f), 22, 16), Rect2D(Vector2f(107.f, 18.f), 22, 16) };
  Rect2D EInvader::LargeInvaderClipFrames[GameConfig::InvaderAnimFramesCount] = { Rect2D(Vector2f(147.f, 19.f), 24, 16), Rect2D(Vector2f(179.f, 19.f), 24, 16) };
}

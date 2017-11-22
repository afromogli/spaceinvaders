#include <cassert>

#include "EInvader.h"
#include "GameConfig.h"
#include "NotSupportedException.h"

namespace SpaceInvaders
{
  EInvader::EInvader(const EntityType invaderType, const shared_ptr<Texture> spriteSheet) : m_spriteSheet{ spriteSheet }, m_invaderType{invaderType}, m_currentFrame{0}
  {
    Rect2D clip = getAnimationClipForType(invaderType, m_currentFrame);
    m_rect.setSize(clip.getWidth(), clip.getHeight());
    m_velocity = GameConfig::InvaderRightVelocity; // Initial speed
    
    assert(spriteSheet->isLoaded());
  }

  Rect2D& EInvader::getAnimationClipForType(const EntityType invaderType, const int currentFrame)
  {
    switch (invaderType)
    {
    case EntityType::SmallInvader:
      return SmallInvaderClipFrames[currentFrame];
    case EntityType::MediumInvader:
      return MediumInvaderClipFrames[currentFrame];
    case EntityType::LargeInvader:
      return LargeInvaderClipFrames[currentFrame];
    default:
      throw new NotSupportedException("The invader type: " + std::to_string(invaderType) + " is not supported.");
    }
  }

  void EInvader::update(const float & deltaTime)
  {
    const float deltaSeconds = deltaTime / 1000; // ms -> s conversion
    const Vector2f nextPosition = getPosition() + m_velocity*deltaSeconds;
    assert(nextPosition.x >= 0 && nextPosition.x + m_rect.getWidth() < GameConfig::WinSize.x);
    setPosition(nextPosition);
  }

  void EInvader::draw(Graphics & graphics)
  {
    m_spriteSheet->render(getPosition(), getAnimationClipForType(m_invaderType, m_currentFrame));
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

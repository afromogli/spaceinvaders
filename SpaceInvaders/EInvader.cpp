#include <cassert>

#include "EInvader.h"
#include "GameConfig.h"
#include "UnsupportedException.h"

namespace SpaceInvaders
{
  EInvader::EInvader(const EntityType invaderType, const shared_ptr<Texture> spriteSheet) : 
    m_spriteSheet{ spriteSheet },
    m_invaderType { invaderType }, 
    m_currentFrame { 0 },
    m_isAlive { true },
    m_drawingCooldown { 0 }
  {
    m_rect.setSize(getSizeForType(invaderType));
    m_velocity = Vector2f(GameConfig::InvaderStartingVelocity, 0); // Initial speed
    
    assert(spriteSheet->isLoaded());
  }

  Vector2f EInvader::getSizeForType(const EntityType invaderType)
  {
    switch (invaderType)
    {
    case EntityType::SmallInvader:
      return GameConfig::InvaderSmallSize;
    case EntityType::MediumInvader:
      return GameConfig::InvaderMediumSize;
    case EntityType::LargeInvader:
      return GameConfig::InvaderLargeSize;
    default:
      throw new UnsupportedException(L"The invader type: " + std::to_wstring(invaderType) + L" is not supported.");
    }
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
      throw new UnsupportedException(L"The invader type: " + std::to_wstring(invaderType) + L" is not supported.");
    }
  }

  void EInvader::update(const float & deltaTime)
  {
    const float deltaSeconds = deltaTime / 1000; // ms -> s conversion
    const Vector2f nextPosition = getPosition() + m_velocity*deltaSeconds;
    assert(nextPosition.x >= 0 && nextPosition.x + m_rect.getWidth() < GameConfig::WinSize.x);
    setPosition(nextPosition);

    if (m_drawingCooldown > 0)
    {
      m_drawingCooldown -= deltaTime;
    }
  }

  void EInvader::draw(Graphics & graphics)
  {
    if (isAlive() && m_drawingCooldown <= 0)
    {
      m_spriteSheet->render(getPosition(), getAnimationClipForType(m_invaderType, m_currentFrame), GameConfig::SpriteScale);
    }    
  }

  void EInvader::changeDirection()
  {
    const Vector2f invaderLeftVelocity = Vector2f(-1.f, 0.f) * m_velocity;
    const Vector2f invaderRightVelocity = m_velocity;

    if (m_velocity == invaderLeftVelocity)
    {
      m_velocity = invaderRightVelocity;
    }
    else
    {
      m_velocity = invaderLeftVelocity;
    }
  }

  void EInvader::changeAnimationFrame()
  {
    m_currentFrame = ++m_currentFrame % GameConfig::InvaderAnimFramesCount;
  }

  bool EInvader::isColliding(const ECannonRocket& rocket) const
  {
    return m_rect.intersects(rocket.getRect());
  }

  bool EInvader::isAlive() const
  {
    return m_isAlive;
  }

  void EInvader::setIsAlive(const bool isAlive)
  {
    m_isAlive = isAlive;
  }

  EntityType EInvader::getType() const
  {
    return m_invaderType;
  }

  int EInvader::getScore() const
  {
    int score = 0;
    switch (getType())
    {
    case EntityType::SmallInvader:
      score = GameConfig::SmallInvaderScore;
      break;
    case EntityType::MediumInvader:
      score = GameConfig::MediumInvaderScore;
      break;
    case EntityType::LargeInvader:
      score = GameConfig::LargeInvaderScore;
      break;
    default:
      throw new UnsupportedException(L"Unsupported invader type");
    }
    return score;
  }

  void EInvader::setDrawingCooldown(const float cooldown)
  {
    m_drawingCooldown = cooldown;
  }

  Rect2D EInvader::SmallInvaderClipFrames[GameConfig::InvaderAnimFramesCount] = { Rect2D(Vector2f(7.f, 18.f), 16, 16), Rect2D(Vector2f(40.f, 18.f), 16, 16) };
  Rect2D EInvader::MediumInvaderClipFrames[GameConfig::InvaderAnimFramesCount] = { Rect2D(Vector2f(74.f, 18.f), 22, 16), Rect2D(Vector2f(107.f, 18.f), 22, 16) };
  Rect2D EInvader::LargeInvaderClipFrames[GameConfig::InvaderAnimFramesCount] = { Rect2D(Vector2f(147.f, 19.f), 24, 16), Rect2D(Vector2f(179.f, 19.f), 24, 16) };
}

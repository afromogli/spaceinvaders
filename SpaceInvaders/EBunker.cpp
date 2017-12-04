#include "EBunker.h"

namespace SpaceInvaders
{
  void EBunker::update(const float& deltaTime)
  {
  }

  void EBunker::draw(Graphics& graphics)
  {
    if (m_isAlive)
    {
      // TODO: fix better bunker damaga gfx, looks like crap right now
      const Rect2D& clip = BunkerAnimClipFrames[int((1.f - m_health / GameConfig::BunkerMaxHealth) * GameConfig::BunkerAnimFramesCount)];
      m_spriteSheet->render(getPosition(), clip, GameConfig::SpriteScale);
    }
  }

  bool EBunker::isColliding(const ECannonRocket& rocket) const
  {
    return m_rect.intersects(rocket.getRect());
  }

  void EBunker::decreaseHealth()
  {
    m_health -= GameConfig::BunkerCannonRocketDamage;
    m_isAlive = m_health > 0.f;
  }

  void EBunker::reset()
  {
    m_health = GameConfig::BunkerMaxHealth;
    m_isAlive = true;
  }

  void EBunker::setIsAlive(const bool isAlive)
  {
    m_isAlive = isAlive;
  }

  bool EBunker::isAlive() const
  {
    return m_isAlive;
  }

  Rect2D EBunker::BunkerAnimClipFrames[GameConfig::BunkerAnimFramesCount] = {
    Rect2D(Vector2f(316.f, 5.f), int(BunkerSpriteSize.x), int(BunkerSpriteSize.y)),
    Rect2D(Vector2f(480.f, 3.f), int(BunkerSpriteSize.x), int(BunkerSpriteSize.y)),
    Rect2D(Vector2f(480.f, 58.f), int(BunkerSpriteSize.x), int(BunkerSpriteSize.y)),
    Rect2D(Vector2f(373.f, 4.f), int(BunkerSpriteSize.x), int(BunkerSpriteSize.y)),
    Rect2D(Vector2f(428.f, 3.f), int(BunkerSpriteSize.x), int(BunkerSpriteSize.y))
  };

  EBunker::EBunker(const shared_ptr<Texture> spriteSheet) : 
    m_health { GameConfig::BunkerMaxHealth }, 
    m_spriteSheet { spriteSheet }, 
    m_isAlive { true }
  {
    m_rect.setSize(GameConfig::BunkerSize);
  }
}

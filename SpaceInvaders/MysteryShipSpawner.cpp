#include "MysteryShipSpawner.h"
#include "GameConfig.h"
#include "Random.h"

namespace SpaceInvaders
{
  MysteryShipSpawner::MysteryShipSpawner(const std::shared_ptr<EMysteryShip> mysteryShip)
  {
    m_mysteryShip = mysteryShip;
    m_timeLeftUntilNextSpawn = getNewRandomTimeLeft();
  }

  void MysteryShipSpawner::trySpawn(const float deltaTime)
  {
    m_timeLeftUntilNextSpawn -= deltaTime;

    if (m_timeLeftUntilNextSpawn <= 0)
    {
      m_mysteryShip->setIsAlive(true);
      // randomize start left or right position
      int direction = Random::getValue(-1, 1);
      if (direction == 0)
      {
        direction = -1;
      }
      m_mysteryShip->setPosition(Vector2f(direction < 0 ? -GameConfig::MysteryShipSize.x : GameConfig::WinSize.x + GameConfig::MysteryShipSize.x, GameConfig::InvaderGroupStartPos.y / 2));
      m_mysteryShip->setVelocity(Vector2f(1 * direction, 0) * GameConfig::MysteryShipSpeed);
      
      m_timeLeftUntilNextSpawn = getNewRandomTimeLeft();
    }
  }

  float MysteryShipSpawner::getNewRandomTimeLeft()
  {
    return Random::getValue(GameConfig::MysteryShipMinSpawnWaitTime, GameConfig::MysteryShipMaxSpawnWaitTime);
  }
}

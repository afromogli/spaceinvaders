#include "InvaderRocketSpawner.h"
#include "ElementNotFoundInCollectionException.h"
#include "Random.h"

namespace SpaceInvaders
{
  InvaderRocketSpawner::InvaderRocketSpawner(const shared_ptr<EInvaderGroup> invaderGroup, const vector<shared_ptr<EInvaderRocket>>& invaderRockets) :
    m_invaderRocketSpawnCooldown { GameConfig::InvaderRocketSpawnMaxCooldown }
  {
    m_invaderGroup = invaderGroup;
    for (const auto rocket : invaderRockets)
    {
      m_invaderRockets.push_back(shared_ptr<EInvaderRocket>(rocket));
    }
  }

  void InvaderRocketSpawner::trySpawn(const float deltaTime)
  {
    if (m_invaderRocketSpawnCooldown <= 0.f && canSpawnInvaderRocket())
    {
      spawnInvaderRocket();
      m_invaderRocketSpawnCooldown = float(Random::getValue(0, int(GameConfig::InvaderRocketSpawnMaxCooldown)));
    }
    else
    {
      m_invaderRocketSpawnCooldown -= deltaTime;
    }
  }

  EInvader& InvaderRocketSpawner::pickRandomInvader() const
  {
    const int col = Random::getValue(0, GameConfig::InvaderColumns - 1);
    const int row = Random::getValue(0, GameConfig::InvaderRows - 1);
    EInvader& invader = m_invaderGroup->getClosestAliveInvaderAtPosition(col, row);
    return invader;
  }

  void InvaderRocketSpawner::spawnInvaderRocket() const
  {
    EInvader invader = pickRandomInvader();
    const Vector2f rocketStartPosition = invader.getRect().getCenter();
    EInvaderRocket& newRocket = getDeadInvaderRocket();
    newRocket.setPosition(rocketStartPosition);
    newRocket.setIsAlive(true);
  }

  EInvaderRocket& InvaderRocketSpawner::getDeadInvaderRocket() const
  {
    for (const auto rocket : m_invaderRockets)
    {
      if (rocket->isAlive() == false)
      {
        return *rocket;
      }
    }
    throw new ElementNotFoundInCollectionException("Could not find any dead invader rocket");
  }

  bool InvaderRocketSpawner::canSpawnInvaderRocket() const
  {
    for (const auto rocket : m_invaderRockets)
    {
      if (rocket->isAlive() == false)
      {
        return true;
      }
    }
    return false;
  }
}

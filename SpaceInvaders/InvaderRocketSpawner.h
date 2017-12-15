#pragma once
#include "EInvaderRocket.h"
#include "EInvader.h"
#include <vector>
#include "EInvaderGroup.h"

namespace SpaceInvaders
{
  class InvaderRocketSpawner
  {
  public:
    InvaderRocketSpawner(const shared_ptr<EInvaderGroup> currentInvaderGroup, const vector<shared_ptr<EInvaderRocket>>& invaderRocketsPool);

    void trySpawn(const float deltaTime);
  private:
    EInvader& pickRandomInvader() const;
    void spawnInvaderRocket() const;
    EInvaderRocket& getDeadInvaderRocket() const;
    bool canSpawnInvaderRocket() const;

    vector<shared_ptr<EInvaderRocket>> m_invaderRocketsPool;
    shared_ptr<EInvaderGroup> m_currInvaderGroup;
    float m_invaderRocketSpawnCooldown;
  };
}

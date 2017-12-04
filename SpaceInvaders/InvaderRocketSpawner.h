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
    InvaderRocketSpawner(const shared_ptr<EInvaderGroup> invaderGroup, const vector<shared_ptr<EInvaderRocket>>& invaderRockets);

    void trySpawn(const float deltaTime);
  private:
    EInvader& pickRandomInvader() const;
    void spawnInvaderRocket() const;
    EInvaderRocket& getDeadInvaderRocket() const;
    bool canSpawnInvaderRocket() const;

    vector<shared_ptr<EInvaderRocket>> m_invaderRockets;
    shared_ptr<EInvaderGroup> m_invaderGroup;
    float m_invaderRocketSpawnCooldown;
  };
}

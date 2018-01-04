#pragma once

#include "EMysteryShip.h"

namespace SpaceInvaders
{
  class MysteryShipSpawner
  {
  public: 
    MysteryShipSpawner(const std::shared_ptr<EMysteryShip> mysteryShip);

    void trySpawn(const float deltaTime);
  private:
    static float getNewRandomTimeLeft();

    float m_timeLeftUntilNextSpawn;
    std::shared_ptr<EMysteryShip> m_mysteryShip;
  };
}
#pragma once

#include <memory>

#include "Entity.h"
#include "EInvader.h"
#include "EInvaderRocket.h"

using namespace Common;

namespace SpaceInvaders
{
  class EInvaderGroup : public Entity
  {
    friend class EntityFactory;
  public:
    
    void update(const float& deltaTime) override;
    void draw(Graphics& graphics) override;
    /**
     * @brief Tries to find the first invader that collides with the specified rocket. Does a bottom (and up) first search for possible collision.
     * @param rocket The rocket
     * @return Returns either the colliding invader or a nullptr
     */
    EInvader* tryFindCollidingInvader(const ECannonRocket& rocket) const;
    EInvader& getClosestAliveInvaderAtPosition(const int column, const int row);
    /**
     * @brief Will reset the invader group, if the gameover flag is false then the velocity will not be reset.
     * @param isGameOver Whether reset is caused by game over state or not.
     */
    void reset(const bool isGameOver);
    static float getDrawingCooldown(const int column, const int row);
    /**
     * @brief Returns the first alive invader starting from the bottom row and upwards.
     * @return First alive invader starting from the bottom row and upwards.
     */
    EInvader* getFirstAliveInvaderFromTheBottom() const;
    bool areAllInvadersDead() const;
    void increaseInvaderVelocity();

  private:
    explicit EInvaderGroup(const shared_ptr<Texture> spriteSheet, const Vector2f upperLeftStartPos);
    bool isAnimationFrameChangeNeeded(const float& deltaTime);
    const EInvader* getFirstAliveInvaderFromTheLeft() const;
    const EInvader* getFirstAliveInvaderFromTheRight() const;
    bool isChangeDirectionNeeded(const float& deltaTime);
    shared_ptr<EInvader> getInvader(const int column, const int row) const;

    static EntityType getInvaderType(int row);
    static Vector2f centerOffset(const EntityType type, Vector2f posOffset);
    Vector2f getInvaderStartPosition(const EntityType type, const int row, const int column) const;

    shared_ptr<EInvader> m_invaders[GameConfig::InvaderRows* GameConfig::InvaderColumns];
    const shared_ptr<Texture> m_spriteSheet;
    float m_timeLeftInAnimationFrame;
    const Vector2f m_upperLeftStartPos;
    static constexpr float ChangeDirectionCooldownLength = 2000.f; // millisecs
    float m_changeDirectionCooldown;
    float m_currentInvaderVelocity;
  };
}
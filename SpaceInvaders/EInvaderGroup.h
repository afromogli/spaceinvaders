#pragma once

#include <memory>

#include "Entity.h"
#include "EInvader.h"

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

  private:
    explicit EInvaderGroup(const shared_ptr<Texture> spriteSheet, const Vector2f upperLeftStartPos);
    bool isAnimationFrameChangeNeeded(const float& deltaTime);
    bool isChangeDirectionNeeded(const float& deltaTime);
    
    static EntityType getInvaderType(int row);
    static void centerOffset(const EntityType type, Vector2f& posOffset);

    shared_ptr<EInvader> m_invaders[GameConfig::InvaderRows* GameConfig::InvaderColumns];

    const shared_ptr<Texture> m_spriteSheet;

    float m_timeLeftInAnimationFrame;

    static constexpr float ChangeDirectionCooldownLength = 2000.f; // millisecs
    float m_changeDirectionCooldown;
  };
}
#pragma once

#include <memory>

#include "Entity.h"
#include "Texture.h"
#include "EntityType.h"
#include "GameConfig.h"
#include "ECannonRocket.h"

using namespace std;
using namespace Common;

namespace SpaceInvaders
{
  class EntityFactory;

  class EInvader : public Entity
  {
    friend class EntityFactory;
  public:
    void update(const float& deltaTime) override;
    void draw(Graphics& graphics) override;
    void changeDirection();
    void changeAnimationFrame();

    bool isColliding(const ECannonRocket& rocket) const;

    bool isAlive() const;
    void setIsAlive(const bool isAlive);
    EntityType getType() const;
    
    int getScore() const;
    /**
     * @brief Sets the drawing cooldown
     * @param cooldown The cooldown period in millisecs 
     */
    void setDrawingCooldown(const float cooldown);

  protected:
    EInvader(EntityType invaderType, const shared_ptr<Texture> spriteSheet);
    const shared_ptr<Texture> m_spriteSheet;
    float m_drawingCooldown;

  private:
    EntityType m_invaderType;
    
    bool m_isAlive;
    int m_currentFrame; // Is either 0 or 1

    static Rect2D SmallInvaderClipFrames[GameConfig::InvaderAnimFramesCount];
    static Rect2D MediumInvaderClipFrames[GameConfig::InvaderAnimFramesCount];
    static Rect2D LargeInvaderClipFrames[GameConfig::InvaderAnimFramesCount];

    static Rect2D& getAnimationClipForType(const EntityType entityType, const int currentFrame);
    static Vector2f getSizeForType(const EntityType invaderType);

  };
}

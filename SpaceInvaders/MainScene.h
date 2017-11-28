#pragma once

#include "Scene.h"
#include "AudioLoader.h"
#include "Entity.h"
#include "ECannon.h"
#include "Texture.h"
#include "EInvaderGroup.h"
#include "EHouse.h"
#include "ECannonRocket.h"
#include "EInvaderRocket.h"

using namespace std;
using namespace Common;

namespace SpaceInvaders
{
  class MainScene : public Scene
  {
  public:
    MainScene(Graphics& graphics, AudioLoader& audioSystem);
    ~MainScene();

    void handleInput(const Uint8 *keyboardState) override;
    void update(const float& deltaTime) override;
    void draw(Graphics& graphics) override;

  private:
    static constexpr int HouseCount = 4;
    
    static int getInvaderScore(EntityType killedInvaderType);
    void updateInvaderRockets();
    void updateCannonRocket();

    enum GameState { Playing, Win, GameOver };

    void updatePlayingState(const float deltaTime);
    EInvader& pickRandomInvader() const;
    void spawnInvaderRocket() const;
    EInvaderRocket& getDeadInvaderRocket() const;
    bool canSpawnInvaderRocket() const;

    vector<shared_ptr<Entity>> m_allEntities;
    shared_ptr<ECannon> m_cannon;
    shared_ptr<EInvaderGroup> m_invaderGroup;
    shared_ptr<EHouse> m_houses[HouseCount];
    shared_ptr<ECannonRocket> m_cannonRocket;
    shared_ptr<EInvaderRocket> m_invaderRockets[GameConfig::InvaderRocketsMaxCount];

    Graphics& m_graphics;
    AudioLoader& m_audioSystem;

    GameState m_currentState = Playing;

    shared_ptr<Texture> m_spriteSheet;

    int m_score;
    float m_invaderRocketSpawnCooldown;
  };
}
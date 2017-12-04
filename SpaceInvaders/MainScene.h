#pragma once

#include "Scene.h"
#include "AudioLoader.h"
#include "Entity.h"
#include "ECannon.h"
#include "Texture.h"
#include "EInvaderGroup.h"
#include "EBunker.h"
#include "ECannonRocket.h"
#include "EInvaderRocket.h"
#include "PlayingUI.h"
#include "EMysteryShip.h"
#include "InvaderRocketSpawner.h"

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
    static constexpr int BunkerCount = 4;
    
    void updateInvaderRockets();
    void updateCannonRocket();

    enum GameState { Playing, Win, GameOver };

    bool hasInvaderGroupHasReachedBottom() const;
    void updatePlayingState(const float deltaTime);

    void resetScene(const bool isGameOver);

    vector<shared_ptr<Entity>> m_allEntities;
    shared_ptr<ECannon> m_cannon;
    shared_ptr<EInvaderGroup> m_invaderGroup;
    shared_ptr<EBunker> m_bunkers[BunkerCount];
    shared_ptr<ECannonRocket> m_cannonRocket;
    vector<shared_ptr<EInvaderRocket>> m_invaderRockets;
    shared_ptr<EMysteryShip> m_mysteryShip;

    Graphics& m_graphics;
    AudioLoader& m_audioSystem;

    GameState m_currentState = Playing;

    shared_ptr<Texture> m_spriteSheet;

    int m_score;
    int m_livesLeft;
    unique_ptr<PlayingUI> m_playingUI;

    unique_ptr<InvaderRocketSpawner> m_invaderRocketSpawner;

    Font m_gameOverFont;
    Text m_gameOverText;
  };
}
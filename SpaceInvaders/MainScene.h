#pragma once

#include "Scene.h"
#include "AudioLoader.h"
#include "Entity.h"
#include "ECannon.h"
#include "Texture.h"
#include "EInvaderGroup.h"

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
    enum GameState { Playing, Win, GameOver };

    void updatePlayingState(const float deltaTime);

    vector<shared_ptr<Entity>> m_allEntities;
    shared_ptr<ECannon> m_cannon;
    shared_ptr<EInvaderGroup> m_invaderGroup;

    Graphics& m_graphics;
    AudioLoader& m_audioSystem;

    GameState m_currentState = Playing;

    shared_ptr<Texture> m_spriteSheet;
  };
}
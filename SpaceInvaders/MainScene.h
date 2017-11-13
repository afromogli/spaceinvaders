#pragma once

#include "Scene.h"
#include "AudioLoader.h"
#include "Entity.h"
#include "ECannon.h"
#include "Texture.h"

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

    Graphics& m_graphics;
    AudioLoader& m_audioSystem;

    GameState m_currentState = Playing;

    Texture m_spriteSheet;
  };
}
#pragma once

#include "Scene.h"
#include "AudioLoader.h"
#include "Entity.h"
//#include "Board.h"
#include "ECannon.h"
#include "Text.h"

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
	  /*shared_ptr<EBall> m_ball;
      Board m_board;*/

      //float m_paddleCooldown; // Millisecs, for collisions

      Graphics& m_graphics;
      AudioLoader& m_audioSystem;

      //void positionBallAbovePaddle() const;

      /*shared_ptr<AudioClip> m_brickSound;
      shared_ptr<AudioClip> m_paddleSound;
      shared_ptr<AudioClip> m_winSound;
      shared_ptr<AudioClip> m_gameoverSound;*/

      GameState m_currentState = Playing;

     /* Font m_font;
      Text m_winText;
      Text m_gameoverText;
      Text m_instructionsText;*/

   };
}


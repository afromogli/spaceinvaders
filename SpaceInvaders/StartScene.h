#pragma once

#include "Scene.h"
#include "Font.h"
#include "Text.h"
#include "AudioLoader.h"

using namespace Common;

namespace SpaceInvaders
{
   class StartScene : public Scene
   {
   public:
      StartScene(Graphics& graphics);
      void handleInput(const Uint8 *keyboardState) override;
      void update(const float& deltaTime) override;
      void draw(Graphics& graphics) override;

   private:
	  Font m_font;
      Text m_spaceInvadersText;
      Text m_instructionsText;
   };
}

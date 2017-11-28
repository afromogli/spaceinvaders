#pragma once
#include "Font.h"
#include "Text.h"

using namespace Common;

namespace SpaceInvaders
{
  class PlayingUI
  {
  public:
    PlayingUI(Graphics& graphics);
    void draw(Graphics& graphics);

    void updateScore(const int newScore);

  private:
    static constexpr float TextUpperPadding = 10.f;
    static constexpr int CharWidth = 26;
    static constexpr int CharHeight = 38;

    Font m_font;
    Text m_scoreLabel;
    Text m_scoreValue;
    Text m_livesLeftLabel;
  };

}

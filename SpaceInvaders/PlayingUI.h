#pragma once
#include "Font.h"
#include "Text.h"
#include "GameConfig.h"
#include "ELife.h"

using namespace Common;

namespace SpaceInvaders
{
  class PlayingUI
  {
  public:
    PlayingUI(Graphics& graphics, const shared_ptr<Texture> spriteSheet, const int livesLeft);
    void draw(Graphics& graphics);

    void setScore(const int newScore);
    void setLivesLeft(const int livesLeft);

  private:
    static constexpr float TextUpperPadding = 10.f;
    static constexpr float LifeUpperPadding = TextUpperPadding + 2.5f;
    static constexpr int CharWidth = 26;
    static constexpr int CharHeight = 38;

    Font m_font;
    Text m_scoreLabel;
    Text m_scoreValue;
    Text m_livesLeftLabel;
    int m_livesLeft;

    shared_ptr<Texture> m_spriteSheet;

    shared_ptr<ELife> m_cannons[GameConfig::LivesMax];
  };

}

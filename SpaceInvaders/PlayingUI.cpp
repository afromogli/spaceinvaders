#include "PlayingUI.h"
#include "GameConfig.h"

namespace SpaceInvaders
{
  PlayingUI::PlayingUI(Graphics& graphics) :
    m_font(GameConfig::GamesFontPath, 25),
    m_scoreLabel("SCORE", Colors::White, Vector2f(20.f, TextUpperPadding), CharWidth, CharHeight, m_font, graphics),
    m_scoreValue("0", Colors::LawnGreen, Vector2f(20.f + CharWidth*6, TextUpperPadding), CharWidth, CharHeight, m_font, graphics), // TODO: fix proper green color
    m_livesLeftLabel("LIVES", Colors::White, Vector2f(GameConfig::WinSize.x-300.f, TextUpperPadding), CharWidth, CharHeight, m_font, graphics)
  {
  }

  void PlayingUI::draw(Graphics& graphics)
  {
    m_scoreLabel.draw(graphics);
    m_scoreValue.draw(graphics);
    m_livesLeftLabel.draw(graphics);
  }

  void PlayingUI::updateScore(const int newScore)
  {
    m_scoreValue.setText(to_string(newScore));
  }
}

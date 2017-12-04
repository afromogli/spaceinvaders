#include "PlayingUI.h"
#include "GameConfig.h"
#include "EntityType.h"
#include "Engine.h"
#include "ELife.h"

namespace SpaceInvaders
{
  PlayingUI::PlayingUI(Graphics& graphics, const shared_ptr<Texture> spriteSheet, const int livesLeft) :
    m_font(GameConfig::GamesFontPath, 25),
    m_scoreLabel(L"SCORE", Colors::White, Vector2f(20.f, TextUpperPadding), CharWidth, CharHeight, m_font, graphics),
    m_scoreValue(L"0", Colors::LawnGreen, Vector2f(20.f + CharWidth*6, TextUpperPadding), CharWidth, CharHeight, m_font, graphics), // TODO: fix proper green color
    m_livesLeftLabel(L"LIVES", Colors::White, Vector2f(GameConfig::WinSize.x-300.f, TextUpperPadding), CharWidth, CharHeight, m_font, graphics),
    m_livesLeft { livesLeft },
    m_spriteSheet { spriteSheet }
  {
    const shared_ptr<CreateEntityWithSpritesheetData> spriteSheetData = std::make_shared<CreateEntityWithSpritesheetData>(m_spriteSheet);
    for (int i = 0; i < GameConfig::LivesMax; i++)
    {
      m_cannons[i] = std::dynamic_pointer_cast<ELife>(Engine::EntityFactoryInstance->createEntity(EntityType::Life, spriteSheetData));
      m_cannons[i]->setPosition(Vector2f(m_livesLeftLabel.getPosition().x + m_livesLeftLabel.getWidth() + CharWidth + i*ELife::CannonAsLifeScale*(ELife::CannonClip.getWidth() + 4), LifeUpperPadding));
    }
  }

  void PlayingUI::draw(Graphics& graphics)
  {
    m_scoreLabel.draw(graphics);
    m_scoreValue.draw(graphics);
    m_livesLeftLabel.draw(graphics);

    for (int i=0; i < m_livesLeft; i++)
    {
      m_cannons[i]->draw(graphics);
    }
  }

  void PlayingUI::setScore(const int newScore)
  {
    m_scoreValue.setText(to_wstring(newScore));
  }

  void PlayingUI::setLivesLeft(const int livesLeft)
  {
    m_livesLeft = livesLeft;
  }
}

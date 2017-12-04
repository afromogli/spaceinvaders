#include "StartScene.h"
#include "GameConfig.h"
#include "Engine.h"
#include "MainScene.h"

namespace SpaceInvaders
{
	StartScene::StartScene(Graphics& graphics) : m_font(GameConfig::GamesFontPath, 200),
		m_spaceInvadersText(L"Space Invaders", Colors::LawnGreen, Vector2f(GameConfig::WinSize.x / 4, GameConfig::WinSize.y / 2 - 100), 36, 100, m_font, graphics),
		m_instructionsText(L"Press enter to start", Colors::White, Vector2f(GameConfig::WinSize.x / 4 + 100, GameConfig::WinSize.y / 2), 16, 60, m_font, graphics)
	{
	}

	void StartScene::handleInput(const Uint8* state)
	{
		if (state[SDL_SCANCODE_RETURN])
		{
			auto engine = Engine::getInstance();
			const auto mainScene = std::make_shared<MainScene>(engine->getGraphics(), engine->getAudioLoader());
			engine->setScene(mainScene);
		}
	}

	void StartScene::update(const float& deltaTime)
	{
	}

	void StartScene::draw(Graphics& graphics)
	{
		m_spaceInvadersText.draw(graphics);
		m_instructionsText.draw(graphics);
	}
}

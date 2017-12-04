#include <SDL.h>

#include "MainScene.h"
#include "Engine.h"
#include "GameConfig.h"
#include "Random.h"
#include "ElementNotFoundInCollectionException.h"
#include "UnsupportedException.h"
#include <cassert>

using namespace Common;

namespace SpaceInvaders
{
  MainScene::MainScene(Graphics& graphics, AudioLoader& audioSystem) :
    m_graphics{ graphics },
    m_audioSystem{ audioSystem },
    m_score{ 0 },
    m_playingUI{ nullptr },
    m_invaderRocketSpawnCooldown{ GameConfig::InvaderRocketSpawnMaxCooldown },
    m_livesLeft{ GameConfig::LivesMax },
    m_gameOverFont(GameConfig::GamesFontPath, 100),
    m_gameOverText(L"GAME OVER", Colors::Red, Vector2f(GameConfig::WinSize.x / 2 - 144.f, GameConfig::WinSize.y / 2 - 100.f), 36, 100, m_gameOverFont, graphics)
  {
    m_spriteSheet = std::make_shared<Texture>(graphics);
    m_spriteSheet->loadFromFile(L"Textures\\spritesheet.png");

    m_playingUI = std::make_unique<PlayingUI>(graphics, m_spriteSheet, m_livesLeft);

    const shared_ptr<CreateEntityWithSpritesheetData> spriteSheetDataPtr = std::make_shared<CreateEntityWithSpritesheetData>(m_spriteSheet);

    m_cannon = std::dynamic_pointer_cast<ECannon>(Engine::EntityFactoryInstance->createEntity(EntityType::Cannon, spriteSheetDataPtr));
    m_cannon->setPosition(GameConfig::InitialCannonPosition);
    m_allEntities.push_back(m_cannon);

    m_invaderGroup = std::dynamic_pointer_cast<EInvaderGroup>(Engine::EntityFactoryInstance->createEntity(EntityType::InvaderGroup, std::make_shared<CreateInvaderGroupEntityData>(m_spriteSheet, GameConfig::InvaderGroupStartPos)));
    m_allEntities.push_back(m_invaderGroup);

    for (int i = 0; i < HouseCount; i++)
    {
      m_houses[i] = std::dynamic_pointer_cast<EHouse>(Engine::EntityFactoryInstance->createEntity(EntityType::House, spriteSheetDataPtr));
      m_houses[i]->setPosition(Vector2f(i * (GameConfig::WinSize.x / HouseCount) + GameConfig::HouseSize.x, 0.f) + GameConfig::HouseVerticalOffset);
      m_allEntities.push_back(m_houses[i]);
    }

    m_cannonRocket = std::dynamic_pointer_cast<ECannonRocket>(Engine::EntityFactoryInstance->createEntity(EntityType::CannonRocket, nullptr));
    m_cannonRocket->setPosition(Vector2f::Zero);
    m_allEntities.push_back(m_cannonRocket);

    for (int i = 0; i < GameConfig::InvaderRocketsMaxCount; i++)
    {
      auto newInvaderRocket = std::dynamic_pointer_cast<EInvaderRocket>(Engine::EntityFactoryInstance->createEntity(EntityType::InvaderRocket, spriteSheetDataPtr));
      newInvaderRocket->setIsAlive(false);
      m_invaderRockets[i] = newInvaderRocket;
      m_allEntities.push_back(newInvaderRocket);
    }
    /*m_gameoverSound = audioSystem.createAndLoadAudioClip("Sounds\\gameover.wav");*/
  }

  MainScene::~MainScene()
  {
  }

  void MainScene::handleInput(const Uint8 *state)
  {
    switch (m_currentState)
    {
    case Playing:
      if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_RIGHT])
      {
        m_cannon->setVelocity(Vector2f::Zero);
      }
      else if (state[SDL_SCANCODE_LEFT])
      {
        m_cannon->setVelocity(Vector2f(-GameConfig::CannonSpeed, 0));
      }
      else if (state[SDL_SCANCODE_RIGHT])
      {
        m_cannon->setVelocity(Vector2f(GameConfig::CannonSpeed, 0));
      }
      else
      {
        m_cannon->setVelocity(Vector2f::Zero);
      }

      if (state[SDL_SCANCODE_SPACE] && m_cannonRocket->isAlive() == false)
      {
        // Spawn rocket
        m_cannonRocket->setPosition(m_cannon->getRect().getCenter());
        m_cannonRocket->setIsAlive(true);
        //cout << "Rocket spawned\n";
      }
      break;
    case GameOver:
    case Win:
      if (state[SDL_SCANCODE_RETURN])
      {
        m_currentState = Playing;
        /* m_winSound->stop();
         m_gameoverSound->stop();*/
        resetScene(true);
      }
      break;
    default:;
    }
  }

  void MainScene::update(const float& deltaTime)
  {
    switch (m_currentState)
    {
    case Playing:
      updatePlayingState(deltaTime);
      break;
    case GameOver:

      break;
    default:;
    }
  }

  void MainScene::draw(Graphics& graphics)
  {
    switch (m_currentState)
    {
    case Playing:
    {
      for (auto entity : m_allEntities)
      {
        entity->draw(graphics);
      }
      m_playingUI->draw(graphics);
      break;
    }
    case GameOver:
    {
      m_playingUI->draw(graphics);
      m_cannon->draw(graphics);
      for (int i = 0; i < HouseCount; i++)
      {
        m_houses[i]->draw(graphics);
      }
      m_gameOverText.draw(graphics);
      break;
    }
    default:
    {
      throw new UnsupportedException(L"Unsupported game state");
    }
    }
  }

  void MainScene::updateInvaderRockets()
  {
    for (int i = 0; i < GameConfig::InvaderRocketsMaxCount; i++)
    {
      EInvaderRocket& currInvRocket = *m_invaderRockets[i];
      if (currInvRocket.isAlive())
      {
        for (int j = 0; j < HouseCount; j++)
        {
          EHouse& currHouse = *m_houses[j];
          if (currHouse.isAlive() && currHouse.isColliding(currInvRocket))
          {
            currHouse.decreaseHealth();
            currInvRocket.setIsAlive(false);
            break;
          }
        }
        if (currInvRocket.isAlive() && m_cannon->isColliding(currInvRocket))
        {
          currInvRocket.setIsAlive(false);
          m_playingUI->setLivesLeft(--m_livesLeft);
          // TODO: show explosion
          if (m_livesLeft == 0)
          {
            m_currentState = GameOver;
          }
        }
      }
    }
  }

  void MainScene::updateCannonRocket()
  {
    if (m_cannonRocket->isAlive())
    {
      for (int i = 0; i < HouseCount; i++)
      {
        EHouse& currHouse = *m_houses[i];
        if (currHouse.isAlive() && currHouse.isColliding(*m_cannonRocket))
        {
          currHouse.decreaseHealth();
          m_cannonRocket->setIsAlive(false);
          break;
        }
      }

      EInvader* collidedInvader = m_invaderGroup->tryFindCollidingInvader(*m_cannonRocket);
      if (collidedInvader != nullptr)
      {
        // TODO: play explosion sound
        // TODO: spawn explosion animation or particle effects
        m_score += collidedInvader->getScore();
        m_playingUI->setScore(m_score);
        collidedInvader->setIsAlive(false);
        m_cannonRocket->setIsAlive(false);
      }
    }
  }

  bool MainScene::hasInvaderGroupHasReachedBottom() const
  {
    const EInvader* invader = m_invaderGroup->getAliveInvaderAtMostBottomPosition();
    assert(invader != nullptr);
    return invader->getPosition().y + invader->getRect().getHeight() >= m_cannon->getPosition().y;
  }

  void MainScene::updatePlayingState(const float deltaTime)
  {
    for (auto entity : m_allEntities)
    {
      entity->update(deltaTime);
    }
    updateCannonRocket();
    updateInvaderRockets();
    if (m_invaderRocketSpawnCooldown <= 0.f && canSpawnInvaderRocket())
    {
      spawnInvaderRocket();
      m_invaderRocketSpawnCooldown = float(Random::getValue(0, int(GameConfig::InvaderRocketSpawnMaxCooldown)));
    }
    else
    {
      m_invaderRocketSpawnCooldown -= deltaTime;
    }

    // Check if player won round
    if (m_invaderGroup->areAllInvadersDead())
    {
      resetScene(false);
      // TODO: increase invader velocity
    }

    if (hasInvaderGroupHasReachedBottom())
    {
      m_currentState = GameOver;
    }
  }

  EInvader& MainScene::pickRandomInvader() const
  {
    const int col = Random::getValue(0, GameConfig::InvaderColumns - 1);
    const int row = Random::getValue(0, GameConfig::InvaderRows - 1);
    EInvader& invader = m_invaderGroup->getClosestAliveInvaderAtPosition(col, row);
    return invader;
  }

  void MainScene::spawnInvaderRocket() const
  {
    EInvader invader = pickRandomInvader();
    const Vector2f rocketStartPosition = invader.getRect().getCenter();
    EInvaderRocket& newRocket = getDeadInvaderRocket();
    newRocket.setPosition(rocketStartPosition);
    newRocket.setIsAlive(true);
  }

  EInvaderRocket& MainScene::getDeadInvaderRocket() const
  {
    for (int i = 0; i < GameConfig::InvaderRocketsMaxCount; i++)
    {
      const auto currRocket = m_invaderRockets[i];
      if (currRocket->isAlive() == false)
      {
        return *currRocket;
      }
    }
    throw new ElementNotFoundInCollectionException("Could not find any dead invader rocket");
  }

  bool MainScene::canSpawnInvaderRocket() const
  {
    for (int i = 0; i < GameConfig::InvaderRocketsMaxCount; i++)
    {
      if (m_invaderRockets[i]->isAlive() == false)
      {
        return true;
      }
    }
    return false;
  }

  void MainScene::resetScene(const bool isGameOver)
  {
    if (isGameOver)
    {
      m_livesLeft = GameConfig::LivesMax;
      m_score = 0;
      m_playingUI->setLivesLeft(m_livesLeft);
      m_playingUI->setScore(m_score);
      m_cannon->setPosition(GameConfig::InitialCannonPosition);
      for (int i = 0; i < HouseCount; i++) {
        m_houses[i]->reset();
      }
    }

    m_invaderGroup->reset();
    
    for (int i = 0; i < GameConfig::InvaderRocketsMaxCount; i++)
    {
      m_invaderRockets[i]->setIsAlive(false);
    }   
  }
}



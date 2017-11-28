#include <SDL.h>

#include "MainScene.h"
#include "Engine.h"
#include "GameConfig.h"
#include <iostream>
#include "NotSupportedException.h"
#include "Random.h"
#include "ElementNotFoundInCollectionException.h"

using namespace Common;

namespace SpaceInvaders
{
  MainScene::MainScene(Graphics& graphics, AudioLoader& audioSystem) :
    m_graphics{ graphics },
    m_audioSystem{ audioSystem },
    m_score{ 0 }, 
    m_playingUI { graphics },
    m_invaderRocketSpawnCooldown { GameConfig::InvaderRocketSpawnMaxCooldown }
  //,
    //m_font("Fonts\\iomanoid.ttf", 100),
    /* m_winText("You win!", Colors::LawnGreen, Vector2f(GameConfig::WinSize.x / 4, GameConfig::WinSize.y / 2 - 100), 500, 100, m_font, graphics),*/
  {
    m_spriteSheet = std::make_shared<Texture>(graphics);
    m_spriteSheet->loadFromFile("Textures\\spritesheet.png");

    const shared_ptr<CreateEntityWithSpritesheetData> spriteSheetDataPtr = std::make_shared<
      CreateEntityWithSpritesheetData>(m_spriteSheet);

    m_cannon = std::dynamic_pointer_cast<ECannon>(
      Engine::EntityFactoryInstance->createEntity(EntityType::Cannon, spriteSheetDataPtr));
    m_cannon->setPosition(GameConfig::InitialCannonPosition);
    m_allEntities.push_back(m_cannon);

    m_invaderGroup = std::dynamic_pointer_cast<EInvaderGroup>(Engine::EntityFactoryInstance->createEntity(
      EntityType::InvaderGroup,
      std::make_shared<CreateInvaderGroupEntityData>(m_spriteSheet, GameConfig::InvaderGroupStartPos)));
    m_allEntities.push_back(m_invaderGroup);

    for (int i = 0; i < HouseCount; i++)
    {
      m_houses[i] = std::dynamic_pointer_cast<EHouse>(
        Engine::EntityFactoryInstance->createEntity(EntityType::House, spriteSheetDataPtr));
      m_houses[i]->setPosition(
        Vector2f(i * (GameConfig::WinSize.x / HouseCount) + GameConfig::HouseSize.x, 0.f) + GameConfig::
        HouseVerticalOffset);
      m_allEntities.push_back(m_houses[i]);
    }

    m_cannonRocket = std::dynamic_pointer_cast<ECannonRocket>(
      Engine::EntityFactoryInstance->createEntity(EntityType::CannonRocket, nullptr));
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
         //m_board.reset();
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
      /*m_ball->setVelocity(Vector2f::Zero);
      positionBallAbovePaddle();*/
      break;
    default:;
    }
  }

  void MainScene::draw(Graphics& graphics)
  {
    /*m_board.draw(graphics);*/
    for (auto entity : m_allEntities)
    {
      entity->draw(graphics);
    }

    m_playingUI.draw(graphics);

    if (m_currentState == Win)
    {
      /*  m_winText.draw(graphics);
        m_instructionsText.draw(graphics);*/
    }
    else if (m_currentState == GameOver)
    {
      /*   m_gameoverText.draw(graphics);
         m_instructionsText.draw(graphics);*/
    }
  }

  int MainScene::getInvaderScore(const EntityType killedInvaderType)
  {
    int newScore = 0;
    switch (killedInvaderType)
    {
    case EntityType::SmallInvader:
      newScore = GameConfig::SmallInvaderScore;
      break;
    case EntityType::MediumInvader:
      newScore = GameConfig::MediumInvaderScore;
      break;
    case EntityType::LargeInvader:
      newScore = GameConfig::LargeInvaderScore;
      break;
    default:
      throw new NotSupportedException("Unsupported invader type");
    }
    return newScore;
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
          // TODO: kill cannon
          // TODO: show explosion
          currInvRocket.setIsAlive(false);
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
        // increase score by checking which invader type that exploded
        m_score += getInvaderScore(collidedInvader->getType());
        m_playingUI.updateScore(m_score);
        collidedInvader->setIsAlive(false);
        m_cannonRocket->setIsAlive(false);
      }
    }
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
    for (int i=0; i < GameConfig::InvaderRocketsMaxCount; i++)
    {
      const auto currRocket = m_invaderRockets[i];
      if (currRocket->isAlive() == false)
      {
        return *currRocket;
      }
    }
    throw new ElementNotFoundInCollectionException("Could not find any dead invader");
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
}



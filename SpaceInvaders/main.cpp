#include <SDL.h>

#include "Engine.h"
#include "MainScene.h"
#include "StartScene.h"

using namespace SpaceInvaders;


int main(int argc, char* args[])
{
	auto engine = Engine::getInstance();
  engine->getGraphics().setRenderScaleQuality("0");
	const auto startScene = std::make_shared<StartScene>(engine->getGraphics());
	engine->setScene(startScene);
	engine->run();
	return 0;
}
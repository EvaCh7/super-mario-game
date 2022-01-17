#include "Game.h"
#include "Config.h"
#include "Map.h"
#include "DisplayTools.h"

Display *display;
ALLEGRO_KEYBOARD_STATE ksKeyboardState;

void Game::MainLoop(void) {
	//while (!IsFinished())
	while(true)
		MainLoopIteration();
	//Map mFirstStage(Config::GetConfig(Config::GetConfig("config/game.json")["maps"][0]["cfg"]));
	//for (int i = 0; i < 100; i++) {
		//Blit(display, 0, 0, mFirstStage.GetMap(), 0 + i * 16, 100 * 16 - 480, 640, 480);
		//al_rest(0.1);
	//}
}

void Game::MainLoopIteration(void) {
	this->RenderHandler();
	this->InputHandler();
	//ProgressAnimations();
	//AI();
	//Physics();
	//CollisionChecking();
	//UserCode(); // hook for custom code at end
	//CommitDestructions();
}
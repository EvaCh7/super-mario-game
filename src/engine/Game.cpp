#include "engine/Game.h"
#include "config/Config.h"
#include "engine/Map.h"
#include "display/DisplayTools.h"

Display *display;
ALLEGRO_KEYBOARD_STATE ksKeyboardState;

void Game::MainLoop(void) {
	while(IsRunning())
		MainLoopIteration();
}

void Game::MainLoopIteration(void) {
	Render();
	Input();
	//ProgressAnimations();
	AI();
	Physics();
	CollisionChecking();
	//UserCode(); // hook for custom code at end
	//CommitDestructions();
}
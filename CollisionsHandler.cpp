#include "engine/Game.h"



void Game::CollisionHandler() {
	/*for (Sprite * s : SpriteManager::GetSingleton().GetDisplayList()) {
		CollisionChecker::GetSingleton().Check();
	}*/
	CollisionChecker::GetSingleton().Check();
}
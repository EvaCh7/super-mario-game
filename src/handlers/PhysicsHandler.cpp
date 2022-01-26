#include "engine/Game.h"

void Game::PhysicsHandler(void) {


	/*
	* Progress Gravity
	*/
	for (Sprite *s : SpriteManager::GetSingleton().GetDisplayList()) {
		/*GravityHandler::ProgressPhysics(s);*/
		s->GetGravityHandler().Check(s->GetBox());
		if (s->GetGravityHandler().IsFalling())
			s->Move(0, 4);
	}

}
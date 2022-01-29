#include "engine/Game.h"

void Game::AIHandler(void) {

	for (Sprite *s : SpriteManager::GetSingleton().GetTypeList("goombas")) {
		int *currX = &s->x;

		if (s->bLooking) {
			if (this->mMap->GetTileLayer()->GetGridLayer()->CanMoveRight(s->GetBox())) {
				s->Move(1, 0);
			}
			else {
				s->bLooking = false;
				s->Move(-1, 0);
			}
		}
		else {
			if (this->mMap->GetTileLayer()->GetGridLayer()->CanMoveLeft(s->GetBox())) {
				s->Move(-1, 0);
			}
			else {
				s->bLooking = true;
				s->Move(1, 0);
			}
		}

	}
	 
	for (Sprite* s : SpriteManager::GetSingleton().GetTypeList("turtles")) {
		if (s->bLooking) {
			if (this->mMap->GetTileLayer()->GetGridLayer()->CanMoveRight(s->GetBox())) {
				s->Move(1, 0);
			}
			else {
				s->bLooking = false;
				s->Move(-1, 0);
			}
		}
		else {
			if (this->mMap->GetTileLayer()->GetGridLayer()->CanMoveLeft(s->GetBox())) {
				s->Move(-1, 0);
			}
			else {
				s->bLooking = true;
				s->Move(1, 0);
			}
		}
	}

}
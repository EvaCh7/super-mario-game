#include "engine/Game.h"

void Game::AIHandler(void) {

	for (Sprite *s : SpriteManager::GetSingleton().GetTypeList("enemy_mushroom")) {
		int *currX = &s->x;

		if (this->mMap->GetTileLayer()->GetGridLayer()->CanMoveLeft(s->GetBox()))
			s->Move(-1, 0);
	}


}
#include "display/DisplayTools.h"
#include "engine/Game.h"

void Game::RenderHandler(void) {
	

	// Display Map
	Blit(display, 0, 0, this->mMap.GetTileLayer().GetBuffer(), 0 + this->iViewWindowX * 16, 100 * 16 - 480, 640, 480);
	//no 16x16 



	for (auto obj : SpriteManager::GetSingleton().GetTypeList("enemy_bird")) {
	
		//obj->Display(display, Rect(16, 480 - 4 * 16, obj->GetBox().w, obj->GetBox().h));
	

		obj->Display(display, Rect(16, 480 - 4 * 16, 16, 16));

	}


	// Display Sprites
	//for Sprite : this->SpriteManager:
		//Blit(display, sprite.x, sprite.y)

	return;
}
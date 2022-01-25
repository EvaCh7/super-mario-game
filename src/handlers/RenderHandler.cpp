#include "display/DisplayTools.h"
#include "engine/Game.h"

void Game::RenderHandler(void) {
	this->mMap.GetTileLayer().Render();
	
	int c = 0;
	for (auto obj : SpriteManager::GetSingleton().GetDisplayList()) {
		obj->Display(this->mMap.GetTileLayer().GetBuffer(), obj->GetBox());
		
		c += 16;
	}

	// Display Map
	Blit(display, 0, 0, this->mMap.GetTileLayer().GetBuffer(), 0 + this->iViewWindowX * 16, 100 * 16 - 480, 640, 480);
	//no 16x16 

	


	// Display Sprites
	//for Sprite : this->SpriteManager:
		//Blit(display, sprite.x, sprite.y)

	return;
}
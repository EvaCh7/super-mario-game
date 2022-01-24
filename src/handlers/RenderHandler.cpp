#include "display/DisplayTools.h"
#include "engine/Game.h"

void Game::RenderHandler(void) {
	
	// Display Map
	Blit(display, 0, 0, this->mMap.GetTileLayer().GetBuffer(), 0 + this->iViewWindowX * 16, 100 * 16 - 480, 640, 480);

	// Display Sprites
	//for Sprite : this->SpriteManager:
		//Blit(display, sprite.x, sprite.y)

	return;
}
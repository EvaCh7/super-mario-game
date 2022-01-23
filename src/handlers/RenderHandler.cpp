#include "display/DisplayTools.h"
#include "engine/Game.h"

void Game::RenderHandler(void) {
	Blit(display, 0, 0, this->mMap.GetTileLayer().GetBuffer(), 0 + this->iViewWindowX * 16, 100 * 16 - 480, 640, 480);
	return;
}
#include "display/DisplayTools.h"
#include "engine/Game.h"

void Game::RenderHandler(void) {
	Rect vw = this->mMap->GetTileLayer()->GetViewWindow();
	
	this->mMap->Display(vw);

	int c = 0;
	for (auto obj : SpriteManager::GetSingleton().GetDisplayList()) {
		obj->Display(this->mMap->GetMap(), obj->GetBox());
		
		c += 16;
	}


	Blit(display, Rect{0, 0, 0, 0}, this->mMap->GetMap(), vw);

	return;
}
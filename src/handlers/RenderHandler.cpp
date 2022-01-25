#include "display/DisplayTools.h"
#include "engine/Game.h"

TileLayer XD;

void Game::RenderHandler(void) {
	//this->mMap.GetTileLayer().Render();
	Rect vw = this->mMap->GetTileLayer().GetViewWindow();
	//printf("AAAMario X:, VW: {%d %d %d %d}\n", vw.x, vw.y, vw.h, vw.w);
	
	XD = this->mMap->GetTileLayer();
	this->mMap->Display(vw);



	int c = 0;
	for (auto obj : SpriteManager::GetSingleton().GetDisplayList()) {
		obj->Display(this->mMap->GetMap(), obj->GetBox());
		
		c += 16;
	}


	//
	//printf("{%d %d %d %d}\n", vw.x, vw.y, vw.h, vw.w);
	Blit(display, Rect{0, 0, 0, 0}, this->mMap->GetMap(), vw);

	return;
}
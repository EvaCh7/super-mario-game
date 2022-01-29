#include "display/DisplayTools.h"
#include "engine/Game.h"

void Game::RenderHandler(void) {
	Rect vw = this->mMap->GetTileLayer()->GetViewWindow();
	
	//this->mMap->Display(vw);
	//for (auto obj : SpriteManager::GetSingleton().GetDisplayList())
	//	obj->Display(this->mMap->GetMap(), obj->GetBox());
	//Blit(display, Rect{0, 0, 0, 0}, this->mMap->GetMap(), vw);

	al_set_target_backbuffer(display);
BlitNoRefresh(display, (Rect&)Rect{0, 0, 640, 480}, this->mMap->GetTileLayer()->GetBuffer(), vw);
for (auto obj : SpriteManager::GetSingleton().GetDisplayList()) {
	Rect sb = obj->GetBox();
/*	Blit(
		dest,
		(Rect&)displayArea,
		this->currFilm->GetBitmap(),
		(Rect&)this->currFilm->GetFrameBox(this->frameNo)
	);*/
	BlitNoRefresh(display, (Rect&)Rect {sb.x - vw.x, sb.y - vw.y, sb.w, sb.h}, obj->currFilm->GetBitmap(), (Rect&)obj->currFilm->GetFrameBox(obj->frameNo));
}
al_flip_display();

	return;
}






// backup

//al_set_target_backbuffer(display);
//BlitNoRefresh(display, (Rect&)Rect{0, 0, 640, 480}, this->mMap->GetTileLayer()->GetBuffer(), vw);
//for (auto obj : SpriteManager::GetSingleton().GetDisplayList()) {
//	Rect sb = obj->GetBox();
///*	Blit(
//		dest,
//		(Rect&)displayArea,
//		this->currFilm->GetBitmap(),
//		(Rect&)this->currFilm->GetFrameBox(this->frameNo)
//	);*/
//	BlitNoRefresh(display, (Rect&)Rect {sb.x - vw.x, sb.y - vw.y, sb.w, sb.h}, obj->currFilm->GetBitmap(), (Rect&)obj->currFilm->GetFrameBox(obj->frameNo));
//}
//al_flip_display();
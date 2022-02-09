#include "display/DisplayTools.h"
#include "engine/Game.h"
#include "engine/Sprite.h"
#include <math.h>

void Game::RenderHandler(void) {
	Rect vw = this->mMap->GetTileLayer()->GetViewWindow();

	//this->mMap->Display(vw);
	//for (auto obj : SpriteManager::GetSingleton().GetDisplayList())
	//	obj->Display(this->mMap->GetMap(), obj->GetBox());
	//Blit(display, Rect{0, 0, 0, 0}, this->mMap->GetMap(), vw);


	//Sprite* mario = SpriteManager::GetSingleton().GetTypeList("mario").front();
	//Rect r = mario->currFilm->GetFrameBox(mario->frameNo);
	//printf("CHAR {%d %d %d %d} {%d %d %d %d}\n", mario->GetBox().x, mario->GetBox().y, mario->GetBox().w, mario->GetBox().h, r.x, r.y, r.w, r.h);


	al_set_target_backbuffer(display);

	BlitNoRefresh(display, (Rect&)Rect { 0, 0, 640, 480 }, this->mMap->GetBackgroundLayer()->GetBuffer(), (Rect&)Rect { (int)floor(0.5 * vw.x), vw.y, vw.w, vw.h });
	//BlitNoRefresh(display, (Rect&)Rect { 0, 0, 640, 480 }, this->mMap->GetUI()->GetBuffer(), (Rect&)Rect { 0, 0, 640, 480 });
	BlitNoRefresh(display, (Rect&)Rect { 0, 0, 640, 480 }, this->mMap->GetTileLayer()->GetBuffer(), vw);



	for (auto obj : SpriteManager::GetSingleton().GetDisplayList()) {
		if (obj->id == "herochar" || obj->id == "smallmario") continue;
		Rect sb = obj->GetBox();
		if (obj->currFilm != nullptr && obj->currFilm->GetTotalFrames() > 0) {
			BlitNoRefresh(display, (Rect&)Rect { sb.x - vw.x, sb.y - vw.y, sb.w, sb.h }, obj->currFilm->GetBitmap(), (Rect&)obj->currFilm->GetFrameBox(obj->frameNo));
		}
		else {
			BlitNoRefresh(display, (Rect&)Rect { sb.x - vw.x, sb.y - vw.y, sb.w, sb.h }, obj->getBitamp(), (Rect&)Rect { 0, 0, 16, 16 });
		}
	}

	// blit mario
	Sprite* s = SpriteManager::GetSingleton().GetTypeList("main").front();
	Rect sb = s->GetBox();
	if (s->currFilm != nullptr && s->currFilm->GetTotalFrames() > 0) {
		BlitNoRefresh(display, (Rect&)Rect { sb.x - vw.x, sb.y - vw.y, sb.w, sb.h }, s->currFilm->GetBitmap(), (Rect&)s->currFilm->GetFrameBox(s->frameNo));
	}
	else {
		BlitNoRefresh(display, (Rect&)Rect { sb.x - vw.x, sb.y - vw.y, sb.w, sb.h }, s->getBitamp(), (Rect&)Rect { 0, 0, 16, 16 });
	}

	
	al_draw_text(this->fFont, al_map_rgb(255, 255, 0), 48, 16, ALLEGRO_ALIGN_CENTER, std::to_string(s->health).c_str());
	al_draw_text(this->fFont, al_map_rgb(255, 255, 0), 48, 32, ALLEGRO_ALIGN_CENTER, std::to_string(this->iCoinCounter).c_str());
	//BlitNoRefresh(display, (Rect&)Rect { 0, 0, 640, 480 }, this->mMap->GetUI()->GetBuffer(), (Rect&)Rect { 0, 0, 640, 480 });
	if(this->bIsGameWon)
		BlitNoRefresh(display, (Rect&)Rect { 0, 0, 640, 480 }, this->bWinScreen, (Rect&)Rect { 0, 0, 640, 480 });

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
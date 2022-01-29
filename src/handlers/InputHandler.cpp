#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "display/DisplayTools.h"
#include "engine/Game.h"

void Game::InputHandler(void) {
	ALLEGRO_EVENT events;
	al_wait_for_event(event_queue, &events);
	al_get_keyboard_state(&ksKeyboardState);

	Sprite* sMario = nullptr;
	for (auto obj : SpriteManager::GetSingleton().GetTypeList("mario")) {
		sMario = obj;

	}

	if (events.type == ALLEGRO_EVENT_TIMER) {
	/*	al_k
		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_SPACE)) {
			if (!sMario->GetGravityHandler().IsJumping() && !sMario->GetGravityHandler().IsFalling())
				sMario->GetGravityHandler().Jump();
		}*/

		int mult = 1;
		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_Z)) {
			mult = 2;
		}
		


		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_SPACE)) {
			if (!sMario->GetGravityHandler().IsJumping() && !sMario->GetGravityHandler().IsFalling()) {
				sMario->GetGravityHandler().Jump();
				/*if (sMario->bLooking) {
					sMario->currFilm = FilmHolder::Get().GetFilm("mario.jumping.right");
				}
				else {
					sMario->currFilm = FilmHolder::Get().GetFilm("mario.jumping.left");
				}*/
			}
		}

		

		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_RIGHT)) {
			sMario->Move(2 * mult, 0);
			
			if (!sMario->GetGravityHandler().IsFalling() && !sMario->GetGravityHandler().IsJumping())
				if(FilmHolder::Get().GetFilm("mario.small.walking.right") != nullptr)
					sMario->currFilm = FilmHolder::Get().GetFilm("mario.small.walking.right");
				else if(FilmHolder::Get().GetFilm("mario.big.walking.left") != nullptr)
					sMario->currFilm = FilmHolder::Get().GetFilm("mario.big.walking.right");
				else
					sMario->currFilm = FilmHolder::Get().GetFilm("turtle.walking.right");
			sMario->SetFrame((sMario->GetFrame() + 1) % sMario->currFilm->GetTotalFrames());
			sMario->bLooking = true;
			//this->iViewWindowX++;
		}
		if(al_key_down(&ksKeyboardState, ALLEGRO_KEY_LEFT)) {
			sMario->Move(-2 * mult, 0);

			if (!sMario->GetGravityHandler().IsFalling() && !sMario->GetGravityHandler().IsJumping())
				if (FilmHolder::Get().GetFilm("mario.small.walking.left") != nullptr)
					sMario->currFilm = FilmHolder::Get().GetFilm("mario.small.walking.left");
				else if (FilmHolder::Get().GetFilm("mario.big.walking.left") != nullptr)
					sMario->currFilm = FilmHolder::Get().GetFilm("mario.big.walking.left");
				else
					sMario->currFilm = FilmHolder::Get().GetFilm("turtle.walking.left");


			sMario->SetFrame((sMario->GetFrame() + 1) % sMario->currFilm->GetTotalFrames());
			sMario->bLooking = false;
			//this->iViewWindowX--;
		}
		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_DOWN)) {
			sMario->Move(0, 2);
		}
		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_UP)) {
			sMario->SetFrame((sMario->GetFrame() + 1 ) % sMario->currFilm->GetTotalFrames());
		}
		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_RIGHT) && al_key_down(&ksKeyboardState, ALLEGRO_KEY_UP)) {
			//sMario->Move(8, 4);
			//this->iViewWindowX--;
		}
		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_ESCAPE))
			this->SetRunning(false);

	}

	return;
}
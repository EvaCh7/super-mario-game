#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "display/DisplayTools.h"
#include "engine/Game.h"

#include "engine/Animations/AnimatorManager.h"
#include "engine/Animations/SystemClock.h"
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

			
			if (AnimatorManager::GetSingleton().mario_walking_animator->HasFinished()) {
				//sMario->currFilm = FilmHolder::Get().GetFilm("mario.walking.right");
				AnimatorManager::GetSingleton().mario_walking_animator->Start(AnimatorManager::GetSingleton().mario_walking_animator->getAnimation(), SystemClock::Get().getgametime());

				AnimatorManager::GetSingleton().MarkAsRunning(AnimatorManager::GetSingleton().mario_walking_animator);

			}


			AnimatorManager::GetSingleton().Progress(SystemClock::Get().getgametime());

			/*
			if (!sMario->GetGravityHandler().IsFalling() && !sMario->GetGravityHandler().IsJumping())
				if(FilmHolder::Get().GetFilm("mario.small.walking.right") != nullptr)
					sMario->currFilm = FilmHolder::Get().GetFilm("mario.small.walking.right");
				else if(FilmHolder::Get().GetFilm("mario.big.walking.left") != nullptr)
					sMario->currFilm = FilmHolder::Get().GetFilm("mario.big.walking.right");
				else
					sMario->currFilm = FilmHolder::Get().GetFilm("herochar.run");*/

			//sMario->SetFrame((sMario->GetFrame() + 1) % sMario->currFilm->GetTotalFrames());
			sMario->bLooking = true;
			sMario->bAttacking = false;
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
					sMario->currFilm = FilmHolder::Get().GetFilm("herochar.run");


			sMario->SetFrame((sMario->GetFrame() + 1) % sMario->currFilm->GetTotalFrames());
			sMario->bLooking = false;
			sMario->bAttacking = false;
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
		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_X)) {
			sMario->bAttacking = true;
			sMario->currFilm = FilmHolder::Get().GetFilm("herochar.attack.sword");
			sMario->SetFrame((sMario->GetFrame() + 1) % sMario->currFilm->GetTotalFrames());
		}
	}

	return;
}
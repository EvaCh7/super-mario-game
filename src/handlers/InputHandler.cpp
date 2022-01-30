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
	for (auto obj : SpriteManager::GetSingleton().GetTypeList("main")) {
		sMario = obj;

	}

	if (events.type == ALLEGRO_EVENT_TIMER) {
		bool bDidSomething = false;
	/*	al_k
		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_SPACE)) {
			if (!sMario->GetGravityHandler().IsJumping() && !sMario->GetGravityHandler().IsFalling())
				sMario->GetGravityHandler().Jump();
		}*/

		int mult = 1;
		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_Z)) {
			mult = 2;
			bDidSomething = true;
		}
		


		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_SPACE)) {
			sMario->CallAction("jump");
			bDidSomething = true;
		}
		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_RIGHT)) {
			sMario->CallAction("run.right");
			bDidSomething = true;
		}
		if(al_key_down(&ksKeyboardState, ALLEGRO_KEY_LEFT)) {
			sMario->CallAction("run.left");
			bDidSomething = true;
		}
		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_DOWN)) {
			sMario->Move(0, 2);
			bDidSomething = true;
		}
		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_UP)) {
			sMario->SetFrame((sMario->GetFrame() + 1 ) % sMario->currFilm->GetTotalFrames());
			bDidSomething = true;
		}
		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_ESCAPE)) {
			this->SetRunning(false);
			bDidSomething = true;
		}

		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_X)) {
			sMario->CallAction("attack.sword");
			bDidSomething = true;
		}
		if (!bDidSomething) {
			sMario->CallAction("idle");
		}
	}

	return;
}
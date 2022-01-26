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

	/*if (events.keyboard.keycode == ALLEGRO_KEY_SPACE) {
		std::cout << "SPACE\n";
	}

	if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (events.keyboard.keycode) {
		case ALLEGRO_KEY_ESCAPE:

			break;
		case ALLEGRO_KEY_SPACE:
			if (!sMario->GetGravityHandler().IsJumping() && !sMario->GetGravityHandler().IsFalling())
				sMario->GetGravityHandler().Jump();
			break;
		}
	}*/

	if (events.type == ALLEGRO_EVENT_TIMER) {
	/*	al_k
		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_SPACE)) {
			if (!sMario->GetGravityHandler().IsJumping() && !sMario->GetGravityHandler().IsFalling())
				sMario->GetGravityHandler().Jump();
		}*/

		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_SPACE)) {
			if (!sMario->GetGravityHandler().IsJumping() && !sMario->GetGravityHandler().IsFalling())
				sMario->GetGravityHandler().Jump();
		}

		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_RIGHT)) {
			sMario->Move(4, 0);
			//this->iViewWindowX++;
		}
		if(al_key_down(&ksKeyboardState, ALLEGRO_KEY_LEFT)) {
			sMario->Move(-4, 0);
			//this->iViewWindowX--;
		}
		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_DOWN)) {
			sMario->Move(0, 4);
		}
		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_RIGHT) && al_key_down(&ksKeyboardState, ALLEGRO_KEY_UP)) {
			//sMario->Move(8, 4);
			//this->iViewWindowX--;
		}

	}

	return;
}
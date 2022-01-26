#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "display/DisplayTools.h"
#include "engine/Game.h"

void Game::InputHandler(void) {
	ALLEGRO_EVENT events;
	al_wait_for_event(event_queue, &events);

	Sprite* sMario = nullptr;
	for (auto obj : SpriteManager::GetSingleton().GetTypeList("mario")) {
		sMario = obj;
	}

	if (events.type == ALLEGRO_EVENT_KEY_UP) {
		switch (events.keyboard.keycode) {
		case ALLEGRO_KEY_ESCAPE:

			break;
		case ALLEGRO_KEY_SPACE:
			sMario->Move(0, -8);
			break;
		}
	}

	if (events.type == ALLEGRO_EVENT_TIMER) {
		al_get_keyboard_state(&ksKeyboardState);

		
		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_RIGHT)) {
			sMario->Move(4, 0);
			//this->iViewWindowX++;
		}
		else if(al_key_down(&ksKeyboardState, ALLEGRO_KEY_LEFT)) {
			sMario->Move(-4, 0);
			//this->iViewWindowX--;
		}
		else if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_UP)) {
			sMario->Move(0, -8);
		}
		else if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_DOWN)) {
			sMario->Move(0, 4);
		}
		else if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_RIGHT) && al_key_down(&ksKeyboardState, ALLEGRO_KEY_UP)) {
			sMario->Move(8, 4);
			//this->iViewWindowX--;
		}

	}

	return;
}
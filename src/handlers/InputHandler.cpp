#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "display/DisplayTools.h"
#include "engine/Game.h"

void Game::InputHandler(void) {
	ALLEGRO_EVENT events;
	al_wait_for_event(event_queue, &events);


	if (events.type == ALLEGRO_EVENT_KEY_UP) {
		switch (events.keyboard.keycode) {
		case ALLEGRO_KEY_ESCAPE:

			break;
		case ALLEGRO_KEY_SPACE:
			
			break;
		}
	}

	Sprite* sMario = nullptr;
	for (auto obj : SpriteManager::GetSingleton().GetTypeList("mario")) {
		sMario = obj;
	}

	if (events.type == ALLEGRO_EVENT_TIMER) {
		al_get_keyboard_state(&ksKeyboardState);
		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_RIGHT)) {
			sMario->Move(16, 0);
			this->iViewWindowX++;
		}
		else if(al_key_down(&ksKeyboardState, ALLEGRO_KEY_LEFT)) {
			sMario->Move(-16, 0);
			this->iViewWindowX--;
		}

	}

	return;
}
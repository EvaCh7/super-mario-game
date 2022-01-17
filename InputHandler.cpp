#include "include/handlers/Handlers.h"
#include "Game.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "DisplayTools.h"

void Game::InputHandler(void) {
	ALLEGRO_EVENT events;
	al_wait_for_event(event_queue, &events);


	if (events.type == ALLEGRO_EVENT_KEY_UP) {
		switch (events.keyboard.keycode) {
		case ALLEGRO_KEY_RIGHT:
			//this->iViewWindowX++;
			break;
		case ALLEGRO_KEY_LEFT:
			//this->iViewWindowX--;
			break;
		case ALLEGRO_KEY_SPACE:
			break;
		}
	}

	if (events.type == ALLEGRO_EVENT_TIMER) {
		al_get_keyboard_state(&ksKeyboardState);
		if (al_key_down(&ksKeyboardState, ALLEGRO_KEY_RIGHT)) {
			this->iViewWindowX++;
		}
		else if(al_key_down(&ksKeyboardState, ALLEGRO_KEY_LEFT)) {
			this->iViewWindowX--;
		}
	}

	return;
}

void Game::RenderHandler(void) {
	Blit(display, 0, 0, this->mMap.GetMap(), 0 + this->iViewWindowX * 16, 100 * 16 - 480, 640, 480);
	return;
}
#include "App.h"
#include "include/handlers/Handlers.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "DisplayTools.h"

void SuperMario::Initialise(void) {
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_install_keyboard();
	display = al_create_display(640, 480);
	this->game.timer = al_create_timer(1.0 / 60);
	this->game.event_queue = al_create_event_queue();
	al_register_event_source(this->game.event_queue, al_get_keyboard_event_source());
	al_register_event_source(this->game.event_queue, al_get_timer_event_source(this->game.timer));
	al_start_timer(this->game.timer);
}

void SuperMario::Load(void) {
	this->game.SetRender(RenderHandler);
	this->game.SetMap(Config::GetConfig(Config::GetConfig("config/game.json")["maps"][0]["cfg"]));

}

SuperMario::SuperMario(void) {

}

void SuperMario::Clear(void) {
	al_destroy_display(display);
}
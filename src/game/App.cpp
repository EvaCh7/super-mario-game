#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "display/DisplayTools.h"
#include <game/App.h>
#include <game/Audio.h>





void SuperMario::Initialise(void) {
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();
	
	Audio audio_sample;
	audio_sample.playSample("config/sound.mp3");

	display = al_create_display(640, 480);
	this->game.timer = al_create_timer(1.0 / 60);
	this->game.event_queue = al_create_event_queue();
	al_register_event_source(this->game.event_queue, al_get_keyboard_event_source());
	al_register_event_source(this->game.event_queue, al_get_timer_event_source(this->game.timer));
	al_start_timer(this->game.timer);
	//audio_sample.stopSample();

}

void SuperMario::Load(void) {
	this->game.SetRender(std::bind(&Game::RenderHandler, &this->game));
	this->game.SetInput(std::bind(&Game::InputHandler, &this->game));
	this->game.SetMap(Config::GetConfig(Config::GetConfig("config/game.json")["maps"][0]["cfg"]));

}

SuperMario::SuperMario(void) {

}

void SuperMario::Clear(void) {
	al_destroy_display(display);
}
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
	//audio_sample.playSample("config/sound.mp3");

	display = al_create_display(640, 480);
	this->game.timer = al_create_timer(1.0 / 60);
	this->game.event_queue = al_create_event_queue();
	al_register_event_source(this->game.event_queue, al_get_keyboard_event_source());
	al_register_event_source(this->game.event_queue, al_get_timer_event_source(this->game.timer));
	al_start_timer(this->game.timer);
	//audio_sample.stopSample();

}

void SuperMario::Load(void) {

	Bitmap* bm = al_load_bitmap(("resources/sprites/marioi.png"));

	json js = Config::GetConfig("config/sprites/mario.json")["small_mario"]["mario_right1"];



	bm=al_create_sub_bitmap(bm, js["x_pos"], js["y_pos"], js["width"], js["height"]);
	Blit(display,0,0 , bm,0,0,16,16);

	this->game.mario = new Sprite(0, 0, bm, js["width"], js["height"]);
	this->game.SetRender(std::bind(&Game::RenderHandler, &this->game));
	this->game.SetInput(std::bind(&Game::InputHandler, &this->game));
	this->game.SetMap(Config::GetConfig(Config::GetConfig("config/game.json")["maps"][1]["cfg"]));

}

SuperMario::SuperMario(void) {

}

void SuperMario::Clear(void) {
	al_destroy_display(display);
}
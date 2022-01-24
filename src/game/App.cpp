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

SpriteManager SpriteManager::singleton;

void addItemToTypeList(std::string id, int x, int y, int width, int height, Bitmap* pngBitmap) {


	std::list <Sprite*> tmp_list;

	
	Bitmap * bm = al_create_sub_bitmap(pngBitmap,x,y,width,height );
	tmp_list.push_back(new Sprite(0, 0, bm, width, height));
	//Blit(display, 0, 0, bm, 0, 0, 16, 16);
	SpriteManager::GetSingleton().Add(new Sprite(0, 0, bm, width,height));
	SpriteManager::GetSingleton().AddTypeList(id, tmp_list);
	tmp_list.clear();
}
void SuperMario::Load(void) {

	Bitmap* bm = al_load_bitmap("resources/sprites/marioi.png");

	Bitmap* bm_enemies = al_load_bitmap("resources/sprites/enemies.png");



	json js_mario = Config::GetConfig("config/sprites/mario.json");
	json js_enemies = Config::GetConfig("config/sprites/enemies.json");



	std::string str = "right1";

	addItemToTypeList("mario", js_mario["small_mario"][str]["x_pos"], js_mario["small_mario"][str]["y_pos"], js_mario["small_mario"][str]["width"], js_mario["small_mario"][str]["height"], bm);
	//addItemToTypeList("big_mario", js_mario["big_mario"]["mario_right_stand"]["x_pos"], js_mario["big_mario"]["mario_right_stand"]["y_pos"], js_mario["big_mario"]["mario_right_stand"]["width"], js_mario["big_mario"]["mario_right_stand"]["height"], bm);
	
	addItemToTypeList("enemy_bird", js_enemies["enemy_bird"][str]["x_pos"], js_enemies["enemy_bird"][str]["y_pos"], js_enemies["enemy_bird"][str]["width"], js_enemies["enemy_bird"][str]["height"], bm_enemies);
	addItemToTypeList("enemy_turtle", js_enemies["enemy_turtle"][str]["x_pos"], js_enemies["enemy_turtle"][str]["y_pos"], js_enemies["enemy_turtle"][str]["width"], js_enemies["enemy_turtle"][str]["height"], bm_enemies);
	
	str = "walk1";
	addItemToTypeList("enemy_mushroom", js_enemies["enemy_mushroom"][str]["x_pos"], js_enemies["enemy_mushroom"][str]["y_pos"], js_enemies["enemy_mushroom"][str]["width"], js_enemies["enemy_mushroom"][str]["height"], bm_enemies);
	str = "state1";

	addItemToTypeList("enemy_piranha_plant", js_enemies["enemy_piranha_plant"][str]["x_pos"], js_enemies["enemy_piranha_plant"][str]["y_pos"], js_enemies["enemy_piranha_plant"][str]["width"], js_enemies["enemy_piranha_plant"][str]["height"], bm_enemies);
	









	//for (auto obj : SpriteManager::GetSingleton().GetTypeList("big_mario")) {

			//Blit(display, 0, 0, obj->getBitamp(), 0, 0, obj->GetBox().w, obj->GetBox().h);
			//Blit(display, 0, 0, obj->getBitamp(), 0, 0, 16, 16);


	//}



	//this->game.mario = new Sprite(0, 0, bm, js["width"], js["height"]);
	this->game.SetRender(std::bind(&Game::RenderHandler, &this->game));
	this->game.SetInput(std::bind(&Game::InputHandler, &this->game));
	this->game.SetMap(Config::GetConfig(Config::GetConfig("config/game.json")["maps"][1]["cfg"]));

}

SuperMario::SuperMario(void) {

}

void SuperMario::Clear(void) {
	al_destroy_display(display);
}
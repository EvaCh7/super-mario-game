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
	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP | ALLEGRO_MIPMAP);
	display = al_create_display(640, 480);
	this->game.timer = al_create_timer(1.0 / 60);
	this->game.event_queue = al_create_event_queue();
	al_register_event_source(this->game.event_queue, al_get_keyboard_event_source());
	al_register_event_source(this->game.event_queue, al_get_timer_event_source(this->game.timer));
	al_start_timer(this->game.timer);
	//audio_sample.stopSample();

}

SpriteManager SpriteManager::singleton;

void addItemToTypeList(std::string id, int x, int y, int width, int height, Bitmap* pngBitmap, int i, int j) {
	std::list <Sprite*> tmp_list;
	
	Bitmap * bm = al_create_sub_bitmap(pngBitmap,x,y,width,height );
	//Blit(display, 0, 0, bm, 0, 0, 16, 16);
	Sprite *s = new Sprite(i, j, bm, width, height);
	tmp_list.push_back(s);
	SpriteManager::GetSingleton().Add(s);
	SpriteManager::GetSingleton().AddTypeList(id, tmp_list);
	tmp_list.clear();
}
void SuperMario::Load(void) {
	Bitmap* bm = al_load_bitmap("resources/sprites/marioi.png");
	Bitmap* bm_enemies = al_load_bitmap("resources/sprites/enemies.png");

	this->game.SetRender(std::bind(&Game::RenderHandler, &this->game));
	this->game.SetInput(std::bind(&Game::InputHandler, &this->game));
	this->game.SetPhysics(std::bind(&Game::PhysicsHandler, &this->game));
	//this->game.SetMap(new Map(Config::GetConfig(Config::GetConfig("config/game.json")["maps"][1]["cfg"])));
	this->game.SetMap(new Map(Config::GetConfig(Config::GetConfig("config/game.json")["maps"][2]["cfg"])));

	json js_mario = Config::GetConfig("config/sprites/mario.json");
	json js_enemies = Config::GetConfig("config/sprites/enemies.json");

	std::string str = "right_stand";

	addItemToTypeList("mario", js_mario["small_mario"][str]["x_pos"], js_mario["small_mario"][str]["y_pos"], js_mario["small_mario"][str]["width"], js_mario["small_mario"][str]["height"], bm, 16 * 3, 100 * 16 - 10 * 16);
	//addItemToTypeList("big_mario", js_mario["big_mario"][str]["x_pos"], js_mario["big_mario"][str]["y_pos"], js_mario["big_mario"][str]["width"], js_mario["big_mario"][str]["height"], bm);
	
	//addItemToTypeList("enemy_bird", js_enemies["enemy_bird"][str]["x_pos"], js_enemies["enemy_bird"][str]["y_pos"], js_enemies["enemy_bird"][str]["width"], js_enemies["enemy_bird"][str]["height"], bm_enemies);
	//addItemToTypeList("enemy_turtle", js_enemies["enemy_turtle"][str]["x_pos"], js_enemies["enemy_turtle"][str]["y_pos"], js_enemies["enemy_turtle"][str]["width"], js_enemies["enemy_turtle"][str]["height"], bm_enemies);
	
	str = "walk1";
	addItemToTypeList("enemy_mushroom", js_enemies["enemy_mushroom"][str]["x_pos"], js_enemies["enemy_mushroom"][str]["y_pos"], js_enemies["enemy_mushroom"][str]["width"], js_enemies["enemy_mushroom"][str]["height"], bm_enemies, 16 * 25, 100 * 16 - 4 * 40);
	str = "state1";

	//addItemToTypeList("enemy_piranha_plant", js_enemies["enemy_piranha_plant"][str]["x_pos"], js_enemies["enemy_piranha_plant"][str]["y_pos"], js_enemies["enemy_piranha_plant"][str]["width"], js_enemies["enemy_piranha_plant"][str]["height"], bm_enemies);

	/*
	* Ready Sprites
	*/
	GridLayer* glLayer = this->game.mMap->GetTileLayer()->GetGridLayer();
	for (Sprite *s : SpriteManager::GetSingleton().GetDisplayList()) {
		/*
		* Default Mover
		*/
		s->SetMover(s->MakeSpriteGridLayerMover(glLayer));

		/*
		* Gravity Handlers
		*/
		s->GetGravityHandler().Enable();
		s->GetGravityHandler().SetOnSolidGroud(
			[glLayer](Rect r){
				return glLayer->IsOnSolidGround(r);
			}
		);
		s->GetGravityHandler().SetOnStartFalling(
			[](void) {
				std::cout << "Mario Starts Falling\n";
				return;
			}
		);
		s->GetGravityHandler().SetOnStopFalling(
			[](void) {
				std::cout << "Mario Stops Falling\n";
				return;
			}
		);

	}

}

SuperMario::SuperMario(void) {

}

void SuperMario::Clear(void) {
	al_destroy_display(display);
}
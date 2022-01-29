#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "display/DisplayTools.h"
#include <game/App.h>
#include <game/Audio.h>

void SuperMario::Initialise(void) {
	json jGameConfig = Config::GetConfig("config/game.json");

	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();
	al_set_new_display_flags(ALLEGRO_FULLSCREEN | ALLEGRO_DIRECT3D_INTERNAL);

	/*
	* Load Game Settings
	*/
	gGameSettings.lWindowWidth = jGameConfig["resolution"]["width"];
	gGameSettings.lWindowHeight = jGameConfig["resolution"]["height"];
	gGameSettings.lFpsLimit = jGameConfig["fps_limit"];
	gGameSettings.fGravity = jGameConfig["physics"]["gravity"];
	gGameSettings.lJumpSpeed = jGameConfig["physics"]["jump_speed"];

	Audio audio_sample;
	//audio_sample.playSample("config/sound.mp3");
	//al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP | ALLEGRO_MIPMAP);
	display = al_create_display(gGameSettings.lWindowWidth, gGameSettings.lWindowHeight);
	if (!display) {
		printf("Could not create display, exiting\n");
		exit(0);
	}

	this->game.timer = al_create_timer(1.0 / gGameSettings.lFpsLimit);
	this->game.event_queue = al_create_event_queue();
	al_register_event_source(this->game.event_queue, al_get_keyboard_event_source());
	al_register_event_source(this->game.event_queue, al_get_timer_event_source(this->game.timer));
	al_start_timer(this->game.timer);
	//audio_sample.stopSample();

}

CollisionChecker CollisionChecker::singleton;
SpriteManager SpriteManager::singleton;
FilmHolder FilmHolder::holder;

void addItemToTypeList(std::string id, int x, int y, int width, int height, Bitmap* pngBitmap, int i, int j) {
	std::list <Sprite*> tmp_list;

	Bitmap* bm = al_create_sub_bitmap(pngBitmap, x, y, width, height);
	Sprite* s = new Sprite(i, j, bm, width, height);
	tmp_list.push_back(s);
	SpriteManager::GetSingleton().Add(s);
	SpriteManager::GetSingleton().AddTypeList(id, tmp_list);
	tmp_list.clear();
}

/*
	initialize which characters collides with whom
	and register action after collision
*/


void registerCollisionsActions() {
	Sprite* mario = SpriteManager::GetSingleton().GetTypeList("mario").front();

	for (Sprite* ubaluba : SpriteManager::GetSingleton().GetTypeList("enemy_mushroom"))
	{
		CollisionChecker::GetSingleton().Register(mario, ubaluba,
			[](Sprite* s1, Sprite* s2) {
				if (s1->GetBox().y < s2->GetBox().y) {
					SpriteManager::GetSingleton().Remove(s2);
					s1->GetGravityHandler().Jump();
					CollisionChecker::GetSingleton().Cancel(s1, s2);
				}
				else {
					printf("mario died from uba luba\n");
				}
			}
		);
	}

	for (Sprite* enemy_bird : SpriteManager::GetSingleton().GetTypeList("enemy_bird"))
	{

		CollisionChecker::GetSingleton().Register(mario, enemy_bird,
			[](Sprite* s1, Sprite* s2) {
				//action if mario collides with uba luba
				//printf("mario collided with birddddddd\n");


				printf("===================================\n");
				if (s1->GetBox().y < s2->GetBox().y) {

					printf("mario smashed bird\n");

					SpriteManager::GetSingleton().RemoveTypeList("enemy_bird", s2);
					SpriteManager::GetSingleton().Remove(s2);
					CollisionChecker::GetSingleton().Cancel(s1, s2);
					s1->GetGravityHandler().Jump();

				}
				else {
					printf("mario died from bird \n");
				}
				printf("===================================\n");


			}
		);




	}

	for (Sprite* enemy_turtle : SpriteManager::GetSingleton().GetTypeList("enemy_turtle"))
	{

		CollisionChecker::GetSingleton().Register(mario, enemy_turtle,
			[](Sprite* s1, Sprite* s2) {
				printf("===================================\n");
				if (s1->GetBox().y < s2->GetBox().y) {

					printf("mario smashed bird\n");

					SpriteManager::GetSingleton().RemoveTypeList("enemy_turtle", s2);
					SpriteManager::GetSingleton().Remove(s2);
					CollisionChecker::GetSingleton().Cancel(s1, s2);
					s1->GetGravityHandler().Jump();

				}
				else {
					printf("mario died from bird \n");
				}
				printf("===================================\n");

			}
		);




	}

	for (Sprite* enemy_piranha_plant : SpriteManager::GetSingleton().GetTypeList("enemy_piranha_plant"))
	{

		CollisionChecker::GetSingleton().Register(mario, enemy_piranha_plant,
			[](Sprite* s1, Sprite* s2) {


				printf("mario died from piranha\n");

				if (s1->GetBox().y < s2->GetBox().y) {

					printf("mario smashed bird\n");

					SpriteManager::GetSingleton().RemoveTypeList("enemy_turtle", s2);
					SpriteManager::GetSingleton().Remove(s2);
					CollisionChecker::GetSingleton().Cancel(s1, s2);
					s1->GetGravityHandler().Jump();

				}
				else {
					printf("mario died from bird \n");
				}
				//action if mario collides with uba luba
				//printf("mario  collided with piranha plant\n");

			}
		);




	}
}

void SuperMario::Load(void) {
	json jGameConfig = Config::GetConfig("config/game.json");
	Bitmap* bm = al_load_bitmap("resources/sprites/marioi.png");
	Bitmap* bm_enemies = al_load_bitmap("resources/sprites/enemies.png");

	/*
	* Set Event Handlers
	*/
	this->game.SetRender(std::bind(&Game::RenderHandler, &this->game));
	this->game.SetInput(std::bind(&Game::InputHandler, &this->game));
	this->game.SetPhysics(std::bind(&Game::PhysicsHandler, &this->game));
	this->game.SetCollisionChecking(std::bind(&Game::CollisionHandler, &this->game));
	this->game.SetAI(std::bind(&Game::AIHandler, &this->game));



	/*
	* Create Map
	*/
	this->game.SetMap(new Map(Config::GetConfig(Config::GetConfig("config/game.json")["maps"][2]["cfg"])));

	/*
	* Create Sprites
	*/
	json js_mario = Config::GetConfig("config/sprites/mario.json");
	json js_enemies = Config::GetConfig("config/sprites/enemies.json");

	std::string str = "right_stand";

	addItemToTypeList("mario", js_mario["small_mario"][str]["x_pos"], js_mario["small_mario"][str]["y_pos"], js_mario["small_mario"][str]["width"], js_mario["small_mario"][str]["height"], bm, 16 * 3, 100 * 16 - 10 * 16);
	
	
	/*
	* MARIO TURBO ANIMATIONS
	*/
	Sprite* mario = SpriteManager::GetSingleton().GetTypeList("mario").front();
	
	FilmHolder::Get().Load("mario.running.right", js_mario["small_mario"]["running_right"], bm);
	FilmHolder::Get().Load("mario.running.left", js_mario["small_mario"]["running_left"], bm);
	FilmHolder::Get().Load("mario.jumping.right", js_mario["small_mario"]["jumping_right"], bm);
	FilmHolder::Get().Load("mario.jumping.left", js_mario["small_mario"]["jumping_left"], bm);

	mario->currFilm = FilmHolder::Get().GetFilm("mario.running.right");












	//addItemToTypeList("big_mario", js_mario["big_mario"][str]["x_pos"], js_mario["big_mario"][str]["y_pos"], js_mario["big_mario"][str]["width"], js_mario["big_mario"][str]["height"], bm);
	str = "right1";
	//addItemToTypeList("enemy_bird", js_enemies["enemy_bird"][str]["x_pos"], js_enemies["enemy_bird"][str]["y_pos"], js_enemies["enemy_bird"][str]["width"], js_enemies["enemy_bird"][str]["height"], bm_enemies, 16 * 26, 100 * 16 - 4 * 40);

	//addItemToTypeList("enemy_turtle", js_enemies["enemy_turtle"][str]["x_pos"], js_enemies["enemy_turtle"][str]["y_pos"], js_enemies["enemy_turtle"][str]["width"], js_enemies["enemy_turtle"][str]["height"], bm_enemies, 16 * 30, 100 * 16 - 4 * 40);

	str = "walk1";
	//addItemToTypeList("enemy_mushroom", js_enemies["enemy_mushroom"][str]["x_pos"], js_enemies["enemy_mushroom"][str]["y_pos"], js_enemies["enemy_mushroom"][str]["width"], js_enemies["enemy_mushroom"][str]["height"], bm_enemies, 16 * 34, 100 * 16 - 4 * 20);
	str = "state1";
	//addItemToTypeList("enemy_piranha_plant", js_enemies["enemy_piranha_plant"][str]["x_pos"], js_enemies["enemy_piranha_plant"][str]["y_pos"], js_enemies["enemy_piranha_plant"][str]["width"], js_enemies["enemy_piranha_plant"][str]["height"], bm_enemies, 16 * 38, 100 * 16 - 4 * 40);


	registerCollisionsActions();




	//addItemToTypeList("enemy_piranha_plant", js_enemies["enemy_piranha_plant"][str]["x_pos"], js_enemies["enemy_piranha_plant"][str]["y_pos"], js_enemies["enemy_piranha_plant"][str]["width"], js_enemies["enemy_piranha_plant"][str]["height"], bm_enemies);

	/*
	* Ready Sprites
	*/
	GridLayer* glLayer = this->game.mMap->GetTileLayer()->GetGridLayer();
	for (Sprite* s : SpriteManager::GetSingleton().GetDisplayList()) {



		/*
		* Default Mover
		*/
		s->SetMover(s->MakeSpriteGridLayerMover(glLayer));

		/*
		* Gravity Handlers
		*/
		s->GetGravityHandler().Enable();
		s->GetGravityHandler().SetOnSolidGroud(
			[glLayer](Rect r) {
				//printf("Fell On: {%d %d %d %d}\n", r.x, r.y, r.w, r.h);
				return glLayer->IsOnSolidGround(r);
			}
		);
		s->GetGravityHandler().SetOnStartFalling(
			[](void) {
				//std::cout << "Mario Starts Falling\n";
				return;
			}
		);
		s->GetGravityHandler().SetOnStopFalling(
			[](void) {
				//std::cout << "Mario Stops Falling\n";
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
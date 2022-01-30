#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "display/DisplayTools.h"
#include <game/App.h>
#include <game/Audio.h>
#include "engine/Sprite.h"

#include "engine/Animations/Animation.h"
#include "engine/Animations/Animator.h"
#include "engine/Animations/AnimatorManager.h"
#include "engine/Animations/SystemClock.h"


void SuperMario::Initialise(void) {
	json jGameConfig = Config::GetConfig("config/game.json");

	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN | ALLEGRO_DIRECT3D_INTERNAL);
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN | ALLEGRO_DIRECT3D_INTERNAL);

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

AnimatorManager AnimatorManager::singleton;

Sprite *addItemToTypeList(std::string id, int x, int y, int width, int height, Bitmap* pngBitmap, int i, int j) {
	Bitmap* bm = al_create_sub_bitmap(pngBitmap, x, y, width, height);
	Sprite* s = new Sprite(i, j, bm, width, height);

	SpriteManager::GetSingleton().Add(s);
	SpriteManager::GetSingleton().AddToTypeList(id, s);

	return s;
}

/*
	initialize which characters collides with whom
	and register action after collision
*/


void registerCollisionsActions(GridLayer *glLayer) {
	Sprite* mario = SpriteManager::GetSingleton().GetTypeList("mario").front();

	for (Sprite* ubaluba : SpriteManager::GetSingleton().GetTypeList("goombas"))
	{
		CollisionChecker::GetSingleton().Register(mario, ubaluba,
			[](Sprite* s1, Sprite* s2) {
				if (s1->GetBox().y < s2->GetBox().y) {
					SpriteManager::GetSingleton().Remove(s2);
					s1->GetGravityHandler().Jump();
					CollisionChecker::GetSingleton().Cancel(s1, s2);
				}
				else {
					if (s1->bAttacking) {
						SpriteManager::GetSingleton().Remove(s2);
						CollisionChecker::GetSingleton().Cancel(s1, s2);
						printf("character sliced goomba");
					}
					else {
						printf("mario died from uba luba\n");
					}
						
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

	for (Sprite* enemy_turtle : SpriteManager::GetSingleton().GetTypeList("turtles"))
	{

		CollisionChecker::GetSingleton().Register(mario, enemy_turtle,
			[](Sprite* s1, Sprite* s2) {
				printf("===================================\n");
				if (s1->GetBox().y < s2->GetBox().y) {

					printf("mario smashed bird\n");

					SpriteManager::GetSingleton().RemoveTypeList("turtles", s2);
					SpriteManager::GetSingleton().Remove(s2);
					CollisionChecker::GetSingleton().Cancel(s1, s2);
					s1->GetGravityHandler().Jump();

				}
				else {
					if (s1->bAttacking) {
						SpriteManager::GetSingleton().Remove(s2);
						CollisionChecker::GetSingleton().Cancel(s1, s2);
						printf("character sliced goomba");
					}
					else {
						printf("mario died from uba luba\n");
					}
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

	for (Sprite* brick : SpriteManager::GetSingleton().GetTypeList("question_brick"))
	{
		CollisionChecker::GetSingleton().Register(mario, brick,
			[glLayer](Sprite* s1, Sprite* s2) {
				printf("MARIO HIT A BRICK\n");
				s1->GetGravityHandler().SetJumping(false);
				//s1->GetGravityHandler().SetFalling(true);
				s1->GetGravityHandler().SetJumpSpeed(1);
				s1->Move(0, 4);


				

				s2->Move(0, -8);

				SpriteManager::GetSingleton().SpawnSprite(Config::GetConfig("config/sprites/enemies.json"), "enemy_turtle", "enemy_turtle", s2->x + 4, s2->y - 32, glLayer);

				s2->Move(0, 8);

				// make block solid
				glLayer->SetGridTileBlock(s2->x / 16, s2->y / 16, GridLayer::GRID_SOLID_TILE);
			}
		);
	}

	for (Sprite* coin : SpriteManager::GetSingleton().GetTypeList("coins"))
	{
		CollisionChecker::GetSingleton().Register(mario, coin,
			[](Sprite* s1, Sprite* s2) {
				printf("MARIO ATE A COIN\n");
				SpriteManager::GetSingleton().RemoveTypeList("coins", s2);
				SpriteManager::GetSingleton().Remove(s2);
				CollisionChecker::GetSingleton().Cancel(s1, s2);

			}
		);
	}
}



void FramList_Action(Sprite* sprite, Animator* animator, const FrameListAnimation& anim) {
	printf("FramList_Action\n");

	FrameListAnimator* frameListAnimator = (FrameListAnimator*)animator;


	/*if (frameRangeAnimator->GetCurrFrame() != anim.GetStartFrame() ||
		frameRangeAnimator->GetCurrRep())*/

	//sprite->Move(((MovingAnimation)anim).GetDx(), ((MovingAnimation)anim).GetDy());
	//frames[getcurrframe()]
	printf("FramList_Action2\n");
	printf("index in frameslist %d\n", frameListAnimator->GetCurrFrame());


	sprite->SetFrame(anim.GetFrames().at(frameListAnimator->GetCurrFrame()));
}



void SuperMario::Load(void) {
	json jGameConfig = Config::GetConfig("config/game.json");
	Bitmap* bm = al_load_bitmap("resources/sprites/marioi.png");
	Bitmap* bm_enemies = al_load_bitmap("resources/sprites/enemies.png");

	int currentMap = 3;

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
	this->game.SetMap(new Map(Config::GetConfig(Config::GetConfig("config/game.json")["maps"][currentMap]["cfg"])));
	
	/*
	* Parse Objects
	*/
	json jMapConfig = Config::GetConfig(Config::GetConfig("config/game.json")["maps"][currentMap]["cfg"]);

	this->game.mMap->ParseObjects(jMapConfig["objects"]);
	SpawnObjects(jMapConfig["objects"]);





	std::vector<unsigned> frames = { 0,1,2 };
	int reps = 1, dx = 2, dy = 0;
	unsigned int delay = 150;

	FrameListAnimation* mario_walking = new FrameListAnimation("mario_walking_right", frames, reps, dx, dy, delay);



	AnimatorManager::GetSingleton().mario_walking_animator = new FrameListAnimator();


	AnimatorManager::GetSingleton().mario_walking_animator->setAnimation(mario_walking);




	//AnimatorManager::GetSingleton().mario_walking_animator->SetOnStart(AnimatorManager::GetSingleton().mario_walking_animator->Start(mario_walking, SystemClock::Get().getgametime());
	Sprite* mario = SpriteManager::GetSingleton().GetTypeList("mario").front();
	

	AnimatorManager::GetSingleton().mario_walking_animator->SetOnAction(
		[mario](Animator* animator, const Animation& anim) {
			FramList_Action(mario, animator, (const FrameListAnimation&)anim);
		}
	);

	AnimatorManager::GetSingleton().mario_walking_animator->SetOnFinish(
		[](Animator* anim) {
			anim->setState(ANIMATOR_STOPPED);
		});

	AnimatorManager::GetSingleton().mario_walking_animator->SetOnStart(
		[](Animator* anim) {
			anim->setState(ANIMATOR_RUNNING);
		});
	AnimatorManager::GetSingleton().Register(AnimatorManager::GetSingleton().mario_walking_animator);






	registerCollisionsActions(this->game.mMap->GetTileLayer()->GetGridLayer());




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
		//s->GetGravityHandler().Enable();
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


bool SuperMario::SpawnObjects(json jObjectConfig) {
	Map *map = this->game.mMap;
	int** lObjLayer = map->GetObjectLayer();

	/*
	* Spawn Sprites
	*/
	for (int i = 0; i < map->GetHeightTileSize(); ++i) {
		for (int j = 0; j < map->GetWidthTileSize(); ++j) {
			for (auto& js : jObjectConfig["bindings"]) {
				if (lObjLayer[i][j] == js["tile"]) {
					std::cout << "(" << i << ", " << j << ") " << js["name"] << std::endl;
					
					if (js["is_external"]) {
						json jExternalConfig = Config::GetConfig(js["external_path"]);
						std::string sExternalName(js["external_name"]);
						Bitmap* bObjBitmap = al_load_bitmap(std::string(jExternalConfig["spritesheet"]).c_str());

						
						/*
						* Parse Animations
						*/
						for (auto& jAnim : jExternalConfig["sprites"][sExternalName]["animations"]) {
							FilmHolder::Get().Load(jAnim["id"], jAnim["animation"], bObjBitmap);
						}

						/*
						* Get default animation
						*/
						Film* fDefaultFilm = FilmHolder::Get().GetFilm(jExternalConfig["sprites"][sExternalName]["default_animation"]);
						Rect rDefaultBox = fDefaultFilm->GetFrameBox(0);
						Sprite* newSprite = addItemToTypeList(js["name"], rDefaultBox.x, rDefaultBox.y, rDefaultBox.w, rDefaultBox.h, bObjBitmap, 16 * j, 16 * i);
						newSprite->currFilm = fDefaultFilm;
						newSprite->GetGravityHandler().Enable();
					}
					else {
						Bitmap* bm = this->game.mMap->GetTiles()[js["tile"]];

						Sprite* s = new Sprite(j * 16, i * 16, bm, 16, 16);
						s->GetGravityHandler().Disable();
							
						SpriteManager::GetSingleton().Add(s);
						SpriteManager::GetSingleton().AddToTypeList(js["name"], s);
					}

				}
			}
		}
	}

	return true;
}
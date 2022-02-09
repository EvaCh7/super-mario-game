#include "engine/Game.h"
#include "engine/Sprite.h"

void Game::AIHandler(void) {

	for (Sprite* s : SpriteManager::GetSingleton().GetTypeList("coin")) {
		s->CallAction("idle");
	}

	for (Sprite* s : SpriteManager::GetSingleton().GetTypeList("waterfall")) {
		s->CallAction("idle");
	}

	for (Sprite* s : SpriteManager::GetSingleton().GetTypeList("finishwaterfall")) {
		s->CallAction("idle");
	}

	for (Sprite* s : SpriteManager::GetSingleton().GetTypeList("slime")) {
		int* currX = &s->x;
		if (s->bDead)
			continue;
		if (s->bLooking) {
			if (this->mMap->GetTileLayer()->GetGridLayer()->CanMoveRight(s->GetBox()))
				s->CallAction("run.right");
			else
				s->CallAction("run.left");
		}
		else {
			if (this->mMap->GetTileLayer()->GetGridLayer()->CanMoveLeft(s->GetBox()))
				s->CallAction("run.left");
			else
				s->CallAction("run.right");
		}
		//s->SetFrame((s->GetFrame() + 1) % s->currFilm->GetTotalFrames());
	}

	for (Sprite* s : SpriteManager::GetSingleton().GetTypeList("goomba")) {
		if (s->bDead)
			continue;
		if (s->bLooking) {
			if (this->mMap->GetTileLayer()->GetGridLayer()->CanMoveRight(s->GetBox())) {
				s->CallAction("run.right");
			}
			else {
				s->CallAction("run.left");
			}
		}
		else {
			if (this->mMap->GetTileLayer()->GetGridLayer()->CanMoveLeft(s->GetBox())) {
				s->CallAction("run.left");
			}
			else {
				s->CallAction("run.right");
			}
		}
		//s->SetFrame((s->GetFrame() + 1) % s->currFilm->GetTotalFrames());
	}

	for (Sprite* s : SpriteManager::GetSingleton().GetTypeList("zombie")) {
		if (s->bDead)
			continue;
		if (s->bLooking) {
			if (this->mMap->GetTileLayer()->GetGridLayer()->CanMoveRight(s->GetBox())) {
				s->CallAction("run.right");
			}
			else {
				s->CallAction("run.left");
			}
		}
		else {
			if (this->mMap->GetTileLayer()->GetGridLayer()->CanMoveLeft(s->GetBox())) {
				s->CallAction("run.left");
			}
			else {
				s->CallAction("run.right");
			}
		}
		//s->SetFrame((s->GetFrame() + 1) % s->currFilm->GetTotalFrames());
	}



	for (Sprite* s : SpriteManager::GetSingleton().GetTypeList("shell")) {
		if (s->bDead) {
			continue;


		}

		if (s->bLooking) {
			if (this->mMap->GetTileLayer()->GetGridLayer()->CanMoveRight(s->GetBox())) {
				s->CallAction("run.right");

			}
			else {
				s->CallAction("run.left");
			}
		}
		else {
			if (this->mMap->GetTileLayer()->GetGridLayer()->CanMoveLeft(s->GetBox())) {
				s->CallAction("run.left");
			}
			else {
				s->CallAction("run.right");
			}
		}
		//s->SetFrame((s->GetFrame() + 1) % s->currFilm->GetTotalFrames());
	}

	for (Sprite* s : SpriteManager::GetSingleton().GetTypeList("boomerang")) {
		if (s->bDead) {
			continue;


		}

		if (s->bLooking) {
			if (this->mMap->GetTileLayer()->GetGridLayer()->CanMoveRight(s->GetBox())) {
				s->CallAction("run.right");

			}
			else {
				SpriteManager::GetSingleton().Remove(s);
				//s->CallAction("run.left");
			}
		}
		else {
			if (this->mMap->GetTileLayer()->GetGridLayer()->CanMoveLeft(s->GetBox())) {
				
				
				s->CallAction("run.left");
			}
			else {
				SpriteManager::GetSingleton().Remove(s);
				s->CallAction("run.right");
			}
		}
		//s->SetFrame((s->GetFrame() + 1) % s->currFilm->GetTotalFrames());
	}

	for (Sprite* s : SpriteManager::GetSingleton().GetTypeList("bigboss")) {

		if (s->bDead)
			continue;


		printf("s->walk: %d\n", s->walk);
		if (s->bLooking) {
			if (this->mMap->GetTileLayer()->GetGridLayer()->CanMoveRight(s->GetBox())) {

				//s->CallAction("attack.sword.right");
				//s->CallAction("attack.sword");
				s->walk = 0;

				s->CallAction("run.right");
			}
			else {



				if (s->walk != 100 && s->walk >= 0) {
					s->CallAction("run.left");

				}
				else if (s->walk == 100) {
					s->CallAction("attack.sword");
					s->walk = -55;


				}

				s->walk++;

			}
		}
		else {
			if (this->mMap->GetTileLayer()->GetGridLayer()->CanMoveLeft(s->GetBox())) {




				if (s->walk != 100 && s->walk >= 0) {
					s->CallAction("run.left");

				}
				else if (s->walk == 100) {
					s->CallAction("attack.sword");
					s->walk = -55;


				}

				s->walk++;

			}
			else {
				
				//s->CallAction("attack.sword.left");

				s->walk = 0;


				s->CallAction("run.right");


				//s->CallAction("run.right");

				//s->CallAction("attack.sword.right");

				//s->CallAction("sword.attack.right");
			}
		}
		//s->SetFrame((s->GetFrame() + 1) % s->currFilm->GetTotalFrames());
	}

}
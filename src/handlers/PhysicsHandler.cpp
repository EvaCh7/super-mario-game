#include "engine/Game.h"

void Game::PhysicsHandler(void) {


	/*
	* Progress Gravity
	*/
	for (Sprite *s : SpriteManager::GetSingleton().GetDisplayList()) {
		GravityHandler &gh = s->GetGravityHandler();
		Sprite* mario = SpriteManager::GetSingleton().GetTypeList("mario").front();
		bool bSolidGround = this->mMap->GetTileLayer()->GetGridLayer()->IsOnSolidGround(s->GetBox());
		/*GravityHandler::ProgressPhysics(s);*/
		//if (gh.IsJumping()) {
		//	gh.SetFalling(false);
		//	gh.SetJumpSpeed(gh.GetJumpSpeed() + gh.GetGravity());
		//	if (gh.GetJumpSpeed() > 0) {
		//		gh.SetJumping(false);
		//		gh.SetFalling(true);
		//	}
		//	
		//	gh.SetYVelocity(gh.GetJumpSpeed());
		//	//s->Move(0, -8);
		//}
		//if (gh.IsFalling() && gh.GetJumpSpeed() < gh.GetBaseSpeed() + 1) {
		//	gh.SetJumpSpeed(gh.GetJumpSpeed() + gh.GetGravity());
		//	gh.SetYVelocity(gh.GetJumpSpeed());
		//}
		//if (gh.GetJumpSpeed() >= gh.GetBaseSpeed()) {
		//	gh.SetFalling(false);
		//	gh.SetJumpSpeed(-gh.GetBaseSpeed());
		//}

		/*gh.Check(s->GetBox());
		if (gh.IsFalling() == false)
			gh.SetYVelocity(0);*/
		//s->Move(0, gh.GetYVelocity());


		//if (gh.IsJumping()) {
		//	gh.SetFalling(false);
		//	gh.SetJumpSpeed(gh.GetJumpSpeed() + gh.GetGravity());
		//	if (gh.GetJumpSpeed() > 0) {
		//		gh.SetJumping(false);
		//		gh.SetFalling(true);
		//		//gh.SetYVelocity(0);
		//		gh.SetJumpSpeed(-gh.GetBaseSpeed());
		//	}
		//	else {
		//		gh.SetYVelocity(gh.GetJumpSpeed());
		//	}
		//}

		//if (gh.IsFalling()) {
		//	gh.SetYVelocity(gh.GetJumpSpeed() + gh.GetGravity());
		//	printf("SET YVEL TO %d\n", gh.GetYVelocity());
		//}
	

		//if(gh.GetYVelocity() != 0)
		//	s->Move(0, gh.GetYVelocity());
		//else {
		//	gh.Check(s->GetBox());
		//	if (gh.IsFalling()) {
		//		s->Move(0, gh.GetYVelocity());
		//	}
		//}


		//gh.Check(s->GetBox());
		/*if (gh.IsFalling())
			s->Move(0, 1);*/
		//std::cout << "Y Velocity: " << gh.GetYVelocity() << std::endl;

		if (bSolidGround) {
			gh.SetFalling(false);
		}

		if (!gh.IsJumping() && !bSolidGround && !gh.IsFalling()) {
			gh.SetFalling(true);
			gh.SetJumping(false);
			gh.SetJumpSpeed(1);
		}

		if (gh.IsJumping() && bSolidGround) {
			//printf("HELLO UWU\n");
			gh.SetJumpSpeed(-gh.GetBaseSpeed());
		}

		if (gh.IsJumping()) {
			gh.SetFalling(false);
			gh.SetJumpSpeed(gh.GetJumpSpeed() + gh.GetGravity());

			if (gh.GetJumpSpeed() > 0) {
				gh.SetJumping(false);
				gh.SetJumpSpeed(1);
				gh.SetFalling(true);
			}
			gh.SetYVelocity(gh.GetJumpSpeed());
		}
		
		if (gh.IsFalling()) {
			gh.SetJumpSpeed(gh.GetJumpSpeed() + gh.GetGravity());
			if (gh.GetYVelocity() > -gh.GetBaseSpeed()) {
				gh.SetYVelocity(gh.GetBaseSpeed());
			}
			gh.SetYVelocity(gh.GetJumpSpeed());
		}



		s->Move(0, gh.GetYVelocity());

		//printf("JUMPING %d FALLING %d ONSOLIDGROUND %d\n", gh.IsJumping(), gh.IsFalling(), this->mMap->GetTileLayer()->GetGridLayer()->IsOnSolidGround(s->GetBox()));
		//std::cout << "Y Velocity: " << gh.GetYVelocity() << std::endl;
	}

}
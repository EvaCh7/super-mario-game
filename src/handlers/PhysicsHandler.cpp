#include "engine/Game.h"

void Game::PhysicsHandler(void) {


	/*
	* Progress Gravity
	*/
	for (Sprite *s : SpriteManager::GetSingleton().GetDisplayList()) {
		GravityHandler &gh = s->GetGravityHandler();
		Sprite* mario = SpriteManager::GetSingleton().GetTypeList("mario").front();
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


		if (gh.IsJumping()) {
			gh.SetFalling(false);
			gh.SetJumpSpeed(gh.GetJumpSpeed() + gh.GetGravity());
			if (gh.GetJumpSpeed() > 0) {
				gh.SetJumping(false);
				gh.SetFalling(true);
				gh.SetYVelocity(0);
				gh.SetJumpSpeed(-gh.GetBaseSpeed());
			}
			else {
				gh.SetYVelocity(gh.GetJumpSpeed());
			}
		}

	

		if(gh.GetYVelocity() != 0)
			s->Move(0, gh.GetYVelocity());
		else {
			gh.Check(s->GetBox());
			if (gh.IsFalling()) {
				s->Move(0, 3);
			}
		}


		//gh.Check(s->GetBox());
		/*if (gh.IsFalling())
			s->Move(0, 1);*/
		//std::cout << "Y Velocity: " << gh.GetYVelocity() << std::endl;
	}

}
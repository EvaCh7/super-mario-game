#include "engine\Physics.h"
#include <iostream>

void GravityHandler::SetOnSolidGroud(std::function<bool(Rect)> f)
{
	this->fOnSolidGroundCallback = f;
}

void GravityHandler::SetOnStartFalling(std::function<void(void)> f)
{
	this->fOnStartFallingCallback = f;
}

void GravityHandler::SetOnStopFalling(std::function<void(void)> f)
{
	this->fOnStopFallingCallback = f;
}

void GravityHandler::Jump(void)
{
	this->bIsJumping = true;
}

//void GravityHandler::ProgressPhysics(Sprite *s)
//{
//	s->GetGravityHandler().Check(s->GetBox());
//	if (s->GetGravityHandler().IsFalling())
//		s->Move(0, 4);
//}

bool GravityHandler::IsJumping(void)
{
	return bIsJumping;
}

bool GravityHandler::IsFalling()
{
	return this->bIsFalling;
}

int GravityHandler::GetGravity(void)
{
	return lGravity;
}

int GravityHandler::GetJumpSpeed(void)
{
	return lJumpSpeed;
}

int GravityHandler::GetBaseSpeed(void)
{
	return this->lBaseJumpSpeed;
}

int GravityHandler::GetYVelocity(void)
{
	return lYVelocity;
}

void GravityHandler::SetJumpSpeed(int lJs)
{
	lJumpSpeed = lJs;
}

void GravityHandler::SetYVelocity(int lYVel)
{
	this->lYVelocity = lYVel;
}

void GravityHandler::SetFalling(bool bFalling)
{
	this->bIsFalling = bFalling;
}

void GravityHandler::SetJumping(bool b)
{
	this->bIsJumping = b;
}

void GravityHandler::Enable(void)
{
	this->bGravityAddicted = true;
}

void GravityHandler::Reset(void)
{
}

void GravityHandler::Check(Rect r)
{
	if (this->bGravityAddicted) {
		//std::cout << "X\n";
		if (this->fOnSolidGroundCallback(r)) {
			if (this->bIsFalling) {
				this->bIsFalling = false;
				this->fOnStopFallingCallback();
			}
		}
		else {
			if (!this->bIsFalling) {
				this->bIsFalling = true;
				this->fOnStartFallingCallback();
			}
		}
	}
}


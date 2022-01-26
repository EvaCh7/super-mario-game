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

//void GravityHandler::ProgressPhysics(Sprite *s)
//{
//	s->GetGravityHandler().Check(s->GetBox());
//	if (s->GetGravityHandler().IsFalling())
//		s->Move(0, 4);
//}

bool GravityHandler::IsFalling()
{
	return this->bIsFalling;
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


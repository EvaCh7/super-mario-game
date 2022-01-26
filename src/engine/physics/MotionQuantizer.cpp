#include "engine/Physics.h"

template <typename Tnum>
int number_sign(Tnum x) {
	return x > 0 ? 1 : x < 0 ? -1 : 0;
}

MotionQuantizer& MotionQuantizer::SetUsed(bool b)
{
	this->bUsed = b;
	return *this;
}

MotionQuantizer& MotionQuantizer::SetRange(int h, int v)
{
	this->lMaxHorizontal = h;
	this->lMaxVertical = v;
	return *this;
}

MotionQuantizer& MotionQuantizer::SetMover(Mover& f)
{
	this->mover = f;
	return *this;
}

void MotionQuantizer::Move(Rect r, int* dx, int* dy) {
	if (!bUsed) {
		mover(r, dx, dy);
	}
	else {
		do {
			auto sign_x = number_sign(*dx);
			auto sign_y = number_sign(*dy);

			auto dxFinal = sign_x * std::min(this->lMaxHorizontal, sign_x * (*dx));
			auto dyFinal = sign_y * std::min(this->lMaxVertical, sign_y * (*dy));
			
			mover(r, &dxFinal, &dyFinal);

			if (!dxFinal)
				*dx = 0;
			else
				*dx -= dxFinal;
			if (!dyFinal)
				*dy = 0;
			else
				*dy -= dyFinal;
		} while (*dx || *dy);
	}
}
#include <engine/Sprite.h>
#include <engine/Map.h>
#include<display/DisplayTools.h>

void SpriteManager::AddTypeList(std::string id, std::list< Sprite*> sprite) {

	this->types.insert({ id,sprite });
	
}
void SpriteManager::Add(Sprite* s) {
	dpyList.push_back(s);
	// insert by ascending zorder
}

void Sprite::Move(int dx, int dy)
{
	
	this->x += dx;
	this->y += dy;
}

void SpriteManager::Remove(Sprite* s) {
	dpyList.remove(s);


}

void MotionQuantizer::Move(const Rect& r, int* dx, int* dy) {
	if (!used)
		mover(r, dx, dy);
	else
		do {
			auto sign_x = number_sign(*dx);
			auto sign_y = number_sign(*dy);
			auto dxFinal = sign_x * std::min(horizMax, sign_x * *dx);
			auto dyFinal = sign_y * std::min(vertMax, sign_y * *dy);
			mover(r, &dxFinal, &dyFinal);
			if (!dxFinal) // X motion denied
				*dx = 0;
			else
				*dx -= dxFinal;
			if (!dyFinal) // Y motion denied
				*dy = 0;
			else
				*dy -= dyFinal;
		} while (*dx || *dy);
}




template <class T> bool clip_rect(
	T x, T y, T w, T h,
	T wx, T wy, T ww, T wh,
	T* cx, T* cy, T* cw, T* ch
) {
	*cw = T(std::min(wx + ww, x + w)) - (*cx = T(std::max(wx, x)));
	*ch = T(std::min(wy + wh, y + h)) - (*cy = T(std::max(wy, y)));
	return *cw > 0 && *ch > 0;
}
bool clip_rect(const Rect& r, const Rect& area, Rect* result) {
	return clip_rect(
		r.x,
		r.y,
		r.w,
		r.h,
		area.x,
		area.y,
		area.w,
		area.h,
		&result->x,
		&result->y,
		&result->w,
		&result->h
	);
}


bool Clipper::Clip(const Rect& r, const Rect& dpyArea, Point* dpyPos, Rect* clippedBox) const {
	Rect visibleArea;
	if (!clip_rect(r, view(), &visibleArea))
	{
		clippedBox->w = clippedBox->h = 0; return false;
	}
	else {
		// clippedBox is in ‘r’ coordinates, sub-rectangle of the input rectangle
		clippedBox->x = r.x - visibleArea.x;
		clippedBox->y = r.y - visibleArea.y;
		clippedBox->w = visibleArea.w;
		clippedBox->h = visibleArea.h;
		dpyPos->x = dpyArea.x + (visibleArea.x - view().x);
		dpyPos->y = dpyArea.y + (visibleArea.y - view().y);
		return true;
	}
}


void Sprite::Display(Bitmap* dest, const Rect& dpyArea) const {


	Rect clippedBox;
	Point dpyPos;

	printf("{%x, %x, %x, %x}\n", dpyArea.x, dpyArea.y, dpyArea.w, dpyArea.h);
	Blit(
		dest,
		(Rect&)dpyArea,
		this->bitmap,
		(Rect&)Rect{0, 0, 16, 16}
		);
	//currFilm->GetBitmap(),//returns mitmap of mariooooooo
		//clippedFrame


	/*

	if (clipper.Clip(GetBox(), dpyArea, &dpyPos, &clippedBox)) {
		Rect clippedFrame{
		frameBox.x + clippedBox.x,
		frameBox.y + clippedBox.y,
		clippedBox.w,
		clippedBox.h
		};
		Blit(
			dest,
			dpyPos,
			this->mario
			//currFilm->GetBitmap(),//returns mitmap of mariooooooo
			clippedFrame,

		);
	}
	*/
	
}
const Clipper MakeTileLayerClipper(TileLayer* layer) {
	return Clipper().SetView(
		[layer](void)
		{ return layer->GetViewWindow(); }
	);
}


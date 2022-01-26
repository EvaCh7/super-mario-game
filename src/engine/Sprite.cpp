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

GravityHandler& Sprite::GetGravityHandler(void)
{
	return this->hGravityHandler;
}

void  SpriteManager::RemoveTypeList(std::string id, Sprite* sprite) {
	this->types[id].remove(sprite);


	
}

MotionQuantizer& Sprite::GetMotionQuantizer(void)
{
	return this->qMotionQuantizer;
}

void Sprite::Move(int dx, int dy)
{
	this->GetMotionQuantizer().Move(this->GetBox(), &dx, &dy);
}

Sprite::Mover Sprite::MakeSpriteGridLayerMover(GridLayer* glLayer) {
	Sprite* s = this;
	return [glLayer, s](Rect r, int* dx, int* dy) {
		glLayer->FilterGridMotion(r, dx, dy);
		if (*dx || *dy) {
			//s->Move(*dx, *dy);
			s->x += *dx;
			s->y += *dy;
		}
	};
}

void SpriteManager::Remove(Sprite* s) {
	dpyList.remove(s);


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


void Sprite::Display(Bitmap* dest, const Rect& dpyArea) const 
{
	Rect clippedBox;
	Point dpyPos;

	Blit(
		dest,
		(Rect&)dpyArea,
		this->bitmap,
		(Rect&)Rect{0, 0, 16, 16}
		);
}
const Clipper MakeTileLayerClipper(TileLayer* layer) {
	return Clipper().SetView(
		[layer](void)
		{ return layer->GetViewWindow(); }
	);
}



/*
		returns iterator to tuples list
		finds if there is a tupple between s1 and s2
*/


auto CollisionChecker::Find(Sprite* s1, Sprite* s2) -> std::list<Entry>::iterator {
	return std::find_if(
		entries.begin(),
		entries.end(),
		[s1, s2](const Entry& e) {
			return std::get<0>(e) == s1 && std::get<1>(e) == s2 ||
				std::get<0>(e) == s2 && std::get<1>(e) == s1;
		}
	);
}



void CollisionChecker::Cancel(Sprite* s1, Sprite* s2) {
	entries.erase(Find(s1, s2));
}



/*
	traverse the list of tuples
	if two sprites did collision
	call the action function of them
*/
void CollisionChecker::Check(void) const {
	for (auto& e : entries)
		if (std::get<0>(e)->CollisionCheck(std::get<1>(e)))
			std::get<2>(e)(std::get<0>(e), std::get<1>(e));
}




bool Sprite::CollisionCheck(Sprite* s) {
	
	if (this->GetBox().x < s->GetBox().x + s->GetBox().w &&
		this->GetBox().x + this->GetBox().w > s->GetBox().x &&
		this->GetBox().y < s->GetBox().y + s->GetBox().h &&
		this->GetBox().h + this->GetBox().y > s->GetBox().y) {
		// collision detected!
		//printf("red dragon called green light\n");
		return true;
		//this.color("green");
	}
	else {
		// no collision
		return false;
		// 
		//this.color("blue");
	}
}
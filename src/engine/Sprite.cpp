#include <engine/Sprite.h>
#include <engine/Map.h>
#include<display/DisplayTools.h>
#include <functional>
#include <iostream>
#include <functional>
#include "engine/Structs.h"
#include "engine/animations/AnimatorManager.h"
#include "engine/animations/SystemClock.h"

void SpriteManager::AddToTypeList(std::string id, Sprite* sprite) {
	GetTypeList(id).push_back(sprite);
	
}
void SpriteManager::Add(Sprite* s) {
	dpyList.push_back(s);
	// insert by ascending zorder
}

void Sprite::RegisterAction(std::string id, std::function<void(Sprite *)> fAction)
{
	vActions[id] = fAction;
}

void Sprite::RegisterDefaultAction(std::string id, std::function<void(Sprite*)> fAction)
{
	vDefaultActions[id] = fAction;
}

void Sprite::RegisterDefaultActions(void)
{
	RegisterDefaultAction("run.left", [](Sprite* s) {
		s->Move(-s->dx, 0);

		Animator* pAnim = AnimatorManager::GetSingleton().GetAnimatorByAnimationID(s->id + ".run.left");
		if (pAnim->HasFinished()) {
			//sMario->currFilm = FilmHolder::Get().GetFilm("mario.walking.right");
			((FrameListAnimator*)pAnim)->Start(((FrameListAnimator*)pAnim)->getAnimation(), SystemClock::Get().getgametime());
			//s->currFilm = FilmHolder::Get().GetFilm(s->id + ".run.left");
			AnimatorManager::GetSingleton().MarkAsRunning(pAnim);
		}


		//s->currFilm = FilmHolder::Get().GetFilm(s->id + ".run.left");
		//s->SetFrame((s->GetFrame() + 1) % s->currFilm->GetTotalFrames());
		s->bLooking = false;
		s->bAttacking = false;
	});

	RegisterDefaultAction("run.right", [](Sprite* s) {
		s->Move(s->dx, 0);

		Animator* pAnim = AnimatorManager::GetSingleton().GetAnimatorByAnimationID(s->id + ".run.right");

		//s->currFilm = FilmHolder::Get().GetFilm(s->id + ".run.right");
		//s->SetFrame((s->GetFrame() + 1) % s->currFilm->GetTotalFrames());
		if (pAnim->HasFinished()) {
			//sMario->currFilm = FilmHolder::Get().GetFilm("mario.walking.right");

			((FrameListAnimator*)pAnim)->Start(((FrameListAnimator*)pAnim)->getAnimation(), SystemClock::Get().getgametime());
			//s->currFilm = FilmHolder::Get().GetFilm(s->id + ".run.right");
			AnimatorManager::GetSingleton().MarkAsRunning(pAnim);
		}



		s->bLooking = true;
		s->bAttacking = false;
	});

	RegisterDefaultAction("jump", [](Sprite* s) {
		if (!s->GetGravityHandler().IsJumping() && !s->GetGravityHandler().IsFalling()) {
			s->GetGravityHandler().Jump();
		}
	});
}

void Sprite::CallAction(std::string id)
{
	std::function<void(Sprite*)> f = vActions[id];
	if (!f) {
		CallDefaultAction(id);
		return;
	}
	f(this);
	return;
}

void Sprite::CallDefaultAction(std::string id)
{
	std::function<void(Sprite*)> f = vDefaultActions[id];
	if (!f)
		return;
	f(this);
	return;
}

GravityHandler& Sprite::GetGravityHandler(void)
{
	return this->hGravityHandler;
}

void SpriteManager::RemoveTypeList(std::string id, Sprite* sprite) {
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
	*cw = T(min(wx + ww, x + w)) - (*cx = T(max(wx, x)));
	*ch = T(min(wy + wh, y + h)) - (*cy = T(max(wy, y)));
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


void Sprite::Display(Bitmap* dest, const Rect& displayArea) const 
{
	Rect clippedBox;
	Point dpyPos;

	Blit(
		dest,
		(Rect&)displayArea,
		this->currFilm->GetBitmap(),
		(Rect&)this->currFilm->GetFrameBox(this->frameNo)
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


auto CollisionChecker::Find(Sprite* s1, Sprite* s2) -> std::vector<Entry>::iterator {
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
	std::vector<Entry>::iterator iter = Find(s1, s2);
	if (iter != entries.end()) {
		entries.erase(iter);

	}
}

void CollisionChecker::Check(void) const {
	for (int i = 0; i < entries.size(); ++i) {
		if (std::get<0>(entries.at(i))->CollisionCheck(std::get<1>(entries.at(i))))
			std::get<2>(entries.at(i))(std::get<0>(entries.at(i)), std::get<1>(entries.at(i)));
	}
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

Sprite* SpriteManager::SpawnSprite(json jObject, std::string sName, std::string id, int x, int y, GridLayer *glLayer) {
	Bitmap* bObjBitmap = al_load_bitmap(std::string(jObject["spritesheet"]).c_str());

	for (auto& jAnim : jObject["sprites"][sName]["animations"]) {
		FilmHolder::Get().Load(jAnim["id"], jAnim["animation"], bObjBitmap);
	}

	Film* fDefaultFilm = FilmHolder::Get().GetFilm(jObject["sprites"][sName]["default_animation"]);
	Rect rDefaultBox = fDefaultFilm->GetFrameBox(0);



	Bitmap* bSpriteBitmap = al_create_sub_bitmap(bObjBitmap, rDefaultBox.x, rDefaultBox.y, rDefaultBox.w, rDefaultBox.h);
	Sprite* s = new Sprite(id, x, y, bSpriteBitmap, rDefaultBox.w, rDefaultBox.h);

	SpriteManager::GetSingleton().Add(s);
	SpriteManager::GetSingleton().AddToTypeList(id, s);

	s->currFilm = fDefaultFilm;
	s->GetGravityHandler().Enable();
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

	Sprite* mario = SpriteManager::GetSingleton().GetTypeList("main").front();
	CollisionChecker::GetSingleton().Register(mario, s,
		[](Sprite* s1, Sprite* s2) {
			printf("===================================\n");
			if (s1->GetBox().y < s2->GetBox().y) {
				SpriteManager::GetSingleton().RemoveTypeList("turtles", s2);
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

	return s;
}
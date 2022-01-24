#ifndef __SPRITE_H__
#define __SPRITE_H__

#include<string>
#include<list>
#include<map>
#include<functional>

#include <engine/Structs.h>


//class Clipper;
//class MotionQuantizer;
//class BoundingArea;

class AnimationFilm;
class Sprite {


public:
	using Mover = std::function<void(const Rect&, int* dx, int* dy)>;
	template <typename Tfunc>
	void SetMover(const Tfunc& f)
	{
		//quantizer.SetMover(mover = f);
	}
	const Rect GetBox(void) const
	{
		return { x, y, frameBox.w, frameBox.h };
	}
	
	void Move(int dx, int dy)
	{
		//quantizer.Move(GetBox(), &dx, &dy);
	}
	


	void SetPos(int _x, int _y) { x = _x; y = _y; }
	void SetZorder(unsigned z) { zorder = z; }
	unsigned GetZorder(void) { return zorder; }
	/*
	void SetFrame(byte i) {
		if (i != frameNo) {
			assert(i < currFilm->GetTotalFrames());
			frameBox = currFilm->GetFrameBox(frameNo = i);
		}
	}
	*/
	


	byte GetFrame(void) const { return frameNo; }
	/*
	void SetBoundingArea(const BoundingArea& area)
	{
		assert(!boundingArea); boundingArea = area.Clone();
	}
	*/
	/*
	void SetBoundingArea(BoundingArea* area)
	{
		assert(!boundingArea); boundingArea = area;
	}
	auto GetBoundingArea(void) const -> const BoundingArea*
	{
		return boundingArea;
	}
	*/
	auto GetTypeId(void) -> const std::string& { return typeId; }
	void SetVisibility(bool v) { isVisible = v; }
	bool IsVisible(void) const { return isVisible; }
	//bool CollisionCheck(const Sprite* s) const;
	void Display(ALLEGRO_DISPLAY* dest, const Rect& dpyArea) const;


	//_x _y poy sponarei o mario
	//100*16 -480 
	Sprite(int _x, int _y, Bitmap * mario,int width,int height) :
		x(_x), y(_y), mario(mario)
	{
		this->frameBox = Rect(_x, _y, width, height);
		//frameNo = currFilm->GetTotalFrames(); SetFrame(0);
	}
	/*
	Sprite(int _x, int _y, AnimationFilm* film, const std::string& _typeId = "") :
		x(_x), y(_y), currFilm(film), typeId(_typeId)
	{
		//frameNo = currFilm->GetTotalFrames(); SetFrame(0);
	}
	*/


private:
	int  frameNo = 0;
	Rect frameBox; // inside the film
	int x = 0, y = 0;
	bool isVisible = false;
	AnimationFilm* currFilm = nullptr;
	//BoundingArea* boundingArea = nullptr;
	unsigned zorder = 0;
	std::string typeId, stateId;
	Mover mover;
	//MotionQuantizer quantizer;
	Bitmap* mario;



};
class SpriteManager final {
public:
	using SpriteList = std::list<Sprite*>;
	using TypeLists = std::map<std::string, SpriteList>;
private:
	SpriteList dpyList;
	TypeLists types;
	static SpriteManager singleton;
public:

	void Add(Sprite* s); // insert by ascending zorder
	void Remove(Sprite* s);
	auto GetDisplayList(void) -> const SpriteList&
	{
		return dpyList;
	}
	auto GetTypeList(const std::string& typeId) -> const SpriteList&
	{
		return types[typeId];
	}
	static auto GetSingleton(void) -> SpriteManager&
	{
		return singleton;
	}
	static auto GetSingletonConst(void) -> const SpriteManager&
	{
		return singleton;
	}
};
template <typename Tnum>
int number_sign(Tnum x) {
	return x > 0 ? 1 : x < 0 ? -1 : 0;
}

class MotionQuantizer {
public:
	using Mover = std::function<void(const Rect& r, int* dx, int* dy)>;
protected:
	int horizMax = 0, vertMax = 0;
	Mover mover; // filters requested motion too!
	bool used = false;
public:
	MotionQuantizer& SetUsed(bool val);
	MotionQuantizer& SetRange(int h, int v)
	{
		horizMax = h, vertMax = v; used = true; return *this;
	}
	MotionQuantizer& SetMover(const Mover& f)
	{
		mover = f; return *this;
	}
	void Move(const Rect& r, int* dx, int* dy);
	MotionQuantizer(void) = default;
	MotionQuantizer(const MotionQuantizer&) = default;
};




class Clipper {
public:
	using View = std::function<const Rect& (void)>;
private:
	View view;
public:
	Clipper& SetView(const View& f)
	{
		view = f; return *this;
	}
	bool Clip(
		const Rect& r,
		const Rect& dpyArea,
		Point* dpyPos,
		Rect* clippedBox
	) const;
	Clipper(void) = default;
	Clipper(const Clipper&) = default;
};

#endif
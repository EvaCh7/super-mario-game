#ifndef __SPRITE_H__
#define __SPRITE_H__

#include<string>
#include<list>
#include<map>
#include<functional>

#include <engine/Structs.h>
#include <engine/Map.h>
#include <engine/Physics.h>

//class Clipper;
//class MotionQuantizer;
//class BoundingArea;

class AnimationFilm;
class Sprite {
public:
	using Mover = std::function<void(const Rect&, int* dx, int* dy)>;
private:

	int  frameNo = 0;
	Rect frameBox; // inside the film
	bool isVisible = false;
	AnimationFilm* currFilm = nullptr;
	//BoundingArea* boundingArea = nullptr;
	unsigned zorder = 0;
	std::string typeId, stateId;
	Mover mover;


	//MotionQuantizer quantizer;
	
	
	Bitmap* bitmap;


	/*
	* Physics
	*/
	GravityHandler hGravityHandler;
	MotionQuantizer qMotionQuantizer;


public:

	/*
	* Physics
	*/
	GravityHandler& GetGravityHandler(void);
	MotionQuantizer& GetMotionQuantizer(void);


	void SetMover(MotionQuantizer::Mover f)
	{
		this->qMotionQuantizer.SetMover(f);
		//quantizer.SetMover(mover = f);
	}
	const Rect GetBox(void) const
	{
		return { x, y, frameBox.w, frameBox.h };
	}
	
	void Move(int dx, int dy);
	
	Bitmap * getBitamp() { return this->bitmap; }

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
	bool CollisionCheck( Sprite* s);
	void Display(Bitmap* dest, const Rect& dpyArea) const;


	//_x _y poy sponarei o mario
	//100*16 -480 
	Sprite(int _x, int _y, Bitmap * bitmap,int width,int height) :
		x(_x), y(_y), bitmap(bitmap)
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

	Mover MakeSpriteGridLayerMover(GridLayer* glLayer);

	int x = 0, y = 0;

};


class SpriteManager final {
public:
	using SpriteList = std::list<Sprite*>;
	using TypeLists = std::map<std::string, SpriteList>;
private:
	std::list<Sprite*> dpyList;
	std::map<std::string, std::list<Sprite*> > types;
	static  SpriteManager singleton;

public:


	void Add(Sprite* s); // insert by ascending zorder
	void Remove(Sprite* s);
	void AddTypeList(std::string id, std::list< Sprite * >  ); // insert by ascending zorder
	void RemoveTypeList(std::string id, Sprite* sprite);
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
//template <typename Tnum>
//int number_sign(Tnum x) {
//	return x > 0 ? 1 : x < 0 ? -1 : 0;
//}

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


class CollisionChecker final {
public:
	using Action = std::function<void(Sprite* s1, Sprite* s2)>;
	static CollisionChecker singleton;
protected:
	using Entry = std::tuple<Sprite*, Sprite*, Action>;
	std::list< std::tuple<Sprite*, Sprite*, Action> > entries;
	/*	
		returns iterator to tuples list
		finds if there is a tupple between s1 and s2 
	*/
	auto Find(Sprite* s1, Sprite* s2)->std::list< std::tuple<Sprite*, Sprite*, Action>>::iterator;
public:
	void Register(Sprite* s1, Sprite* s2, const Action& f)
	{
		//assert(!In(s1, s2)); 
		entries.push_back(std::make_tuple(s1, s2, f));
	}
	void Cancel(Sprite* s1, Sprite* s2);
	void Check(void) const;
	static auto GetSingleton(void) -> CollisionChecker&
	{
		return singleton;
	}
	static auto GetSingletonConst(void) -> const CollisionChecker&
	{
		return singleton;
	}
};


#endif
#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <functional>
#include "Structs.h"
#include "Map.h"
#include<engine/Sprite.h>

extern Display *display;
extern ALLEGRO_KEYBOARD_STATE ksKeyboardState;

class Game {
public:
	using Action = std::function<void(void)>;
	using Pred = std::function<bool(void)>;
	Action	pauseResume;
	bool		isPaused = false;
	uint64_t	pauseTime = 0;
	Map *mMap;

	ALLEGRO_TIMER *timer;
	ALLEGRO_EVENT_QUEUE *event_queue;
private:
	Action render, anim, input, ai, physics, destruct, collisions, user;
	Pred done;
	void Invoke (const Action& f) { if (f) f(); }
	int iViewWindowX;
	int iJumpVel;
public:
	void InputHandler(void);
	void RenderHandler(void);
	void PhysicsHandler(void);
	void CollisionHandler(void);
	void AIHandler(void);

	/*
	* Getters
	*/
	void Render(void) { Invoke(render); }
	void ProgressAnimations(void) { Invoke(anim); }
	void Input(void) { Invoke(input); }
	void AI(void) { Invoke(ai); }
	void Physics(void) { Invoke(physics); }
	void CollisionChecking(void) { Invoke(collisions); }
	void CommitDestructions(void) { Invoke(destruct); }
	void UserCode(void) { Invoke(user); }
	bool IsFinished(void) const { return !done(); }
	void MainLoop(void);
	void MainLoopIteration(void);
	void SetOnPauseResume(const Action& f)
	{
		pauseResume = f;
	}
	void Pause(uint64_t t)
	{
		isPaused = true; pauseTime = t; Invoke(pauseResume);
	}
	void Resume(void)
	{
		isPaused = false; Invoke(pauseResume); pauseTime = 0;
	}
	bool IsPaused(void) const
	{
		return isPaused;
	}
	uint64_t GetPauseTime(void) const
	{
		return pauseTime;
	}
	/*
	* Setters
	*/
	void SetRender (const Action & f) { render = f; }
	void SetProgressAnimations (const Action & f) { anim = f; }
	void SetInput (const Action &f) { input = f; }
	void SetAI (const Action &f) { ai = f; }
	void SetPhysics (const Action &f) { physics = f; }
	void SetCollisionChecking (const Action &f) { collisions = f; }
	void SetCommitDestructions (const Action &f) { destruct = f; }
	void SetUserCode (const Action &f) { user = f; }
	void SetMap(Map *map) { mMap = map; }
};
#endif
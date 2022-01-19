#ifndef __APP_H__
#define __APP_H__

#include "engine/Game.h"

class App {
protected:
	Game game;

public:
	virtual void	Initialise(void) = 0;
	virtual void	Load(void) = 0;
	virtual void	Run(void) { game.MainLoop(); }
	virtual void	RunIteration(void)
	{
		game.MainLoopIteration();
	}
	Game &GetGame(void) { return game; }
	const Game &GetGame(void) const { return game; }
	virtual void	Clear(void) = 0;
	void Main(void) {
		Initialise();
		Load();
		Run();
		Clear();
	}
};

class SuperMario : public App {
	void Initialise(void);
	void Load(void);
	void Clear(void);
public:
	SuperMario();
};
#endif
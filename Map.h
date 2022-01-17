#ifndef __MAP_H__
#define __MAP_H__

#include "Config.h"
#include "Structs.h"

class Map {
private:
	std::map<int, Bitmap *> mTiles;

public:
	Map(json jConfig);

	std::map<int, Bitmap *> GetTiles();
};

#endif
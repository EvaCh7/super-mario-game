#ifndef __MAP_H__
#define __MAP_H__

#include "config/Config.h"
#include "engine/Structs.h"

class Map {
private:
	std::map<int, Bitmap *> mTiles;
	Bitmap *bMap;
	int iTileWidth, iTileHeight;

	void DrawTilemapToMap(Bitmap *bTarget, std::string sTilemapPath);

public:
	Map(json jConfig);
	Map();

	std::map<int, Bitmap *> GetTiles();

	Bitmap *GetMap();
};

#endif
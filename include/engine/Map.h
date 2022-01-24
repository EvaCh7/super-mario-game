#ifndef __MAP_H__
#define __MAP_H__

#include "config/Config.h"
#include "engine/Structs.h"

class TileLayer {
private:
	
	/*
	* Tile Map
	*/
	int** iTileMap;
	int iRows, iCols;


	std::map<int, Bitmap*> mTileSet; // Tile set

	Rect rViewWindow;
	Bitmap* bBuffer;

public:

	/*
	* Tile Map
	*/
	void SetTile(int iCol, int iRow, int iIndex);
	int GetTile(int iCol, int iRow);

	/*
	* View Window
	*/
	const Rect& GetViewWindow(void) const;
	void SetViewWindow(const Rect& rRect);

	/*
	* Buffer
	*/
	Bitmap* GetBuffer(void);

	/*
	* Parse Tile Map
	*/
	bool ParseCSV(std::string sPath);


	void Display(ALLEGRO_DISPLAY* bDest, const Rect& rDisplayArea);
	void Scroll(float fDx, float fDy);

	TileLayer(int iRows, int iCols, std::map<int, Bitmap*> mTileSet);
	TileLayer(void);
};

class Grid {

};

class Map {
private:

	/*
	* Tile Layer
	*/
	TileLayer tlLayer;

	std::map<int, Bitmap *> mTiles;
	Bitmap *bMap;
	int iTileWidth, iTileHeight;

public:

	/*
	* Tile Layer
	*/
	TileLayer GetTileLayer(void);

	Map(json jConfig);
	Map();

	std::map<int, Bitmap *> GetTiles();

	Bitmap *GetMap();
};



#endif
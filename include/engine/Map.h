#ifndef __MAP_H__
#define __MAP_H__

#include "config/Config.h"
#include "engine/Structs.h"


class GridLayer {
private:
	int** vGrid = nullptr;
	unsigned sTotal = 0;
	int iRows, iCols;

	static const byte GRID_THIN_AIR_MASK		= 0x00;
	static const byte GRID_LEFT_SOLID_MASK		= 0x01;
	static const byte GRID_RIGHT_SOLID_MASK		= 0x02;
	static const byte GRID_TOP_SOLID_MASK		= 0x04;
	static const byte GRID_BOTTOM_SOLID_MASK	= 0x08;
	static const byte GRID_GROUD_MASK			= 0x10;
	static const byte GRID_FLOATING_MASK		= 0x20;
	static const byte GRID_EMPTY_TILE			= GRID_FLOATING_MASK;
	static const byte GRID_SOLID_TILE			= (GRID_LEFT_SOLID_MASK | GRID_RIGHT_SOLID_MASK | GRID_TOP_SOLID_MASK | GRID_BOTTOM_SOLID_MASK);

public:

	/*
	* Grid Tile Setting
	*/
	void SetGridTile(int iCol, int iRow, int iIndex);
	int GetGridTile(int iCol, int iRow);
	void SetSolidGridTile(int iCol, int iRow);
	void SetEmptyGridTile(int iCol, int iRow);
	void SetGridTileFlags(int iCol, int iRow, int fFlags);
	void SetGridTileTopSolidOnly(int iCol, int iRow);
	bool CanPassGridTile(int iCol, int iRow, int fFlags);

	void FilterGridMotion(const Rect& rRect, int iDx, int iDy) const;
	bool IsOnSolidGround(const Rect& rRect) const;
	
	int** GetBuffer(void);
	const int** GetBuffer(void) const;

	/*
	* Computation
	*/
	void ComputeTileGridBlocks(int **tlTileMap);
	void SetGridTileBlock(int iCol, int iRow, int iFlag);

	/*
	* Utils
	*/
	void Print(void);

	GridLayer(int iRows, int iCols);
};

class TileLayer {
private:

	/*
	* Tile Map
	*/
	int** iTileMap;
	int iRows, iCols;

	/*
	* Grid
	*/
	GridLayer glLayer;

	std::map<int, Bitmap*> mTileSet; // Tile set

	Rect rViewWindow;
	Bitmap* bBuffer;

public:

	void Render(void);

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
#include <fstream>
#include <stdlib.h>
#include "engine/Map.h"
#include "tools/json.h"
#include "tools/csv_parser.h"
#include "display/DisplayTools.h"
#include "engine/Sprite.h"


void Map::Display(Rect rViewWindow)
{
	Blit(this->bMap, rViewWindow, this->GetTileLayer()->GetBuffer(), rViewWindow);
}

TileLayer *Map::GetTileLayer(void)
{
	return this->tlLayer;
}

Map::Map(json jConfig) {
	Bitmap *bm = al_load_bitmap(std::string(jConfig["tiles"]["path"]).c_str());

	this->bMap = al_create_bitmap(300 * 16, 100 * 16);

	/*
	* Create tile set
	*/
	this->iTileHeight = jConfig["tiles"]["height"];
    this->iTileWidth = jConfig["tiles"]["width"];
	int counter = 0;
	for (int i = 0; i < al_get_bitmap_height(bm) / this->iTileHeight; ++i) {
		for (int j = 0; j < al_get_bitmap_width(bm) / this->iTileWidth; ++j) {
			this->mTiles.insert({ counter, al_create_sub_bitmap(bm, j * this->iTileHeight, i * this->iTileWidth, this->iTileHeight, this->iTileWidth) });
			counter++;
		}
	}

	/*
	* Create Tile Layer and parse layers
	*/
	TileLayer *tlLayer = new TileLayer(100, 300, this->mTiles);
	tlLayer->SetViewWindow(Rect{0, 100 * 16 - 480, 640, 480});
	json jMaps = jConfig["map"];
	for (auto& itMap : jMaps) {
		tlLayer->ParseCSV(itMap["path"]);
	}
	this->tlLayer = tlLayer;
}


std::map<int, Bitmap *> Map::GetTiles() {
	return this->mTiles;
}

Bitmap *Map::GetMap() {
	return this->bMap;
}

void TileLayer::SetTile(int iCol, int iRow, int iIndex)
{
	this->iTileMap[iRow][iCol] = iIndex;
}

int TileLayer::GetTile(int iCol, int iRow)
{
	return this->iTileMap[iRow][iCol];
}

Rect TileLayer::GetViewWindow(void)
{
	Sprite* sMario = nullptr;
	for (auto obj : SpriteManager::GetSingleton().GetTypeList("mario")) {
		sMario = obj;
	}





	if (sMario->x > this->rViewWindow.x + this->rViewWindow.w) {
		ScrollWithBoundsCheck(&this->rViewWindow, 16, 0);
		//this->SetViewWindow(Rect{this->rViewWindow.x + 640, this->rViewWindow.y, this->rViewWindow.w, this->rViewWindow.h});
	}
	else if (sMario->x <= this->rViewWindow.x) {
		ScrollWithBoundsCheck(&this->rViewWindow, -16, 0);
		//this->SetViewWindow(Rect{ this->rViewWindow.x - 640, this->rViewWindow.y, this->rViewWindow.w, this->rViewWindow.h });
	}
	else if (sMario->y > this->rViewWindow.y + this->rViewWindow.h) {
		ScrollWithBoundsCheck(&this->rViewWindow, 0, 16);
		//this->SetViewWindow(Rect{ this->rViewWindow.x, this->rViewWindow.y + 480, this->rViewWindow.w, this->rViewWindow.h });
	}
	else if (sMario->y <= this->rViewWindow.y) {
		ScrollWithBoundsCheck(&this->rViewWindow, 0, -16);
		//this->SetViewWindow(Rect{ this->rViewWindow.x, this->rViewWindow.y - 480, this->rViewWindow.w, this->rViewWindow.h });
	}

	return this->rViewWindow;
}

void TileLayer::SetViewWindow(Rect rRect)
{
	//printf("IMMA SET VW TO {%d %d %d %d}!\n", rRect.x, rRect.y, rRect.w, rRect.h);
	this->rViewWindow = rRect;
}

Bitmap* TileLayer::GetBuffer(void)
{
	return this->bBuffer;
}

bool TileLayer::ParseCSV(std::string sPath)
{
	std::ifstream iFile(sPath);
	std::string sIndex = "";

	int i = 0, j = 0;
	while (std::getline(iFile, sIndex, ',')) {
		this->iTileMap[i][j] = stoi(sIndex);

		if (sIndex.find("\n") != std::string::npos) {
			i++;
			j = 0;
		} 
		else {
			j++;
		}
	}

	Render();

	this->glLayer.ComputeTileGridBlocks(this->iTileMap);
	//this->glLayer.Print();
	return false;
}

void TileLayer::Scroll(Rect* rViewWindow, int iDx, int iDy)
{
	rViewWindow->x += iDx;
	rViewWindow->y += iDy;
	return;
}

bool TileLayer::CanScrollHorizontal(Rect rViewWindow, int iDx)
{
	return rViewWindow.x >= -iDx &&
			(rViewWindow.x + rViewWindow.w + iDx) <= 300 * 16;
}

bool TileLayer::CanScrollVertical(Rect rViewWindow, int iDy)
{
	return rViewWindow.y >= -iDy &&
		(rViewWindow.y + rViewWindow.h + iDy) <= 100 * 16;
}

void TileLayer::FilterScrollDistance(int viewStartCoord, int viewSize, int* d, int maxMapSize)
{
	auto val = *d + viewStartCoord;
	if (val < 0)
		*d = viewStartCoord;
	else if (viewSize >= maxMapSize)
		*d = 0;
	else if ((val + viewSize) >= maxMapSize)
		*d = maxMapSize - (viewStartCoord + viewSize);

}

void TileLayer::FilterScroll(Rect rViewWindow, int* dx, int* dy)
{
	FilterScrollDistance(rViewWindow.x, rViewWindow.w, dx, 300 * 16);
	FilterScrollDistance(rViewWindow.y, rViewWindow.h, dy, 100 * 16);
}

void TileLayer::ScrollWithBoundsCheck(Rect* rViewWindow, int dx, int dy)
{
	FilterScroll(*rViewWindow, &dx, &dy);
	Scroll(rViewWindow, dx, dy);
}

void TileLayer::Render(void) {

	for (int i = 0; i < this->iRows; ++i) {
		for (int j = 0; j < this->iCols; ++j) {
			if (this->iTileMap[i][j] != -1)
				Blit(this->bBuffer, j * 16, i * 16, this->mTileSet[this->iTileMap[i][j]], 0, 0, 16, 16);
		}
	}
}

void TileLayer::Display(ALLEGRO_DISPLAY* bDest, const Rect& rDisplayArea)
{
	// todo: blit display area to bDest
}

void TileLayer::Scroll(float fDx, float fDy)
{
	// todo: move vwindow
}

TileLayer::TileLayer(int iRows, int iCols, std::map<int, Bitmap*> mTileSet) :
	rViewWindow(Rect{ 0, 0, 0, 0 }),
	glLayer(iRows * 4, iCols * 4),
	mTileSet(mTileSet),
	iRows(iRows),
	iCols(iCols)
{
	// Allocate
	this->iTileMap = new int* [iRows];
	for (int i = 0; i < iRows; ++i) {
		this->iTileMap[i] = new int[iCols];
		memset(this->iTileMap[i], -1, iCols * sizeof(int)); // not sure if needed
	}
	this->bBuffer = al_create_bitmap(300 * 16, 100 * 16); // screen buffer (to zwgrafismeno to-be map)
}



void GridLayer::ComputeTileGridBlocks(int** tlTileMap)
{
	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 300; ++j) {
			if (tlTileMap[i][j] == 79) {
				this->SetGridTileBlock(j, i, GridLayer::GRID_SOLID_TILE);
			}
		}
	}
}

void GridLayer::SetGridTileBlock(int iCol, int iRow, int iFlag)
{
	for (int i = iRow; i < iRow + 4; ++i) {
		for (int j = iCol; j < iCol + 4; ++j) {
			this->SetGridTile(j, i, iFlag);
		}
	}
}

void GridLayer::Print(void)
{
	for (int i = 0; i < this->iRows; ++i) {
		std::cout << "[";
		for (int j = 0; j < this->iCols; ++j) {
			if(this->vGrid[i][j] == GridLayer::GRID_SOLID_TILE) std::cout << this->vGrid[i][j] << ", ";
		}
		std::cout << "]" << std::endl;
	}
}

GridLayer::GridLayer(int iRows, int iCols) :
	iRows(iRows),
	iCols(iCols)
{
	// Allocate
	this->sTotal = iRows * iCols;
	this->vGrid = new int* [iRows];
	for (int i = 0; i < iRows; ++i) {
		this->vGrid[i] = new int[iCols];
		memset(this->vGrid[i], GridLayer::GRID_EMPTY_TILE, iCols * sizeof(int)); // not sure if needed
	}
}

void GridLayer::SetGridTile(int iCol, int iRow, int iIndex)
{
	this->vGrid[iRow][iCol] = iIndex;
	return;
}

int GridLayer::GetGridTile(int iCol, int iRow)
{
	return this->vGrid[iRow][iCol];
}

void GridLayer::SetSolidGridTile(int iCol, int iRow)
{
	this->SetGridTile(iCol, iRow, GridLayer::GRID_SOLID_TILE);
}

void GridLayer::SetGridTileFlags(int iCol, int iRow, int fFlags)
{
	this->SetGridTile(iCol, iRow, fFlags);
}

#ifndef __DISPLAY_TOOLS_H__
#define __DISPLAY_TOOLS_H__

#include "engine/Structs.h"

void Blit(Bitmap *dest, unsigned int destX, unsigned int destY, Bitmap *src, unsigned int srcX, unsigned int srcY, unsigned int width, unsigned int height);
void Blit(ALLEGRO_DISPLAY *dest, unsigned int destX, unsigned int destY, Bitmap *src, unsigned int srcX, unsigned int srcY, unsigned int width, unsigned int height);





void Blit(Bitmap* dDest, Rect& rDest, Bitmap* dSrc, Rect& rSrc);
void Blit(Display* dest, const Rect& rDest, Bitmap* src, const Rect& rSrc);


void DrawViewWindow(Display *dDisplay, unsigned int iDestX, unsigned int iDestY, Bitmap *bSource, unsigned int iSrcX, unsigned int iSrcY, unsigned int iWidth, unsigned int iHeight);

void RenderHandler(void);

//struct ViewData {
//	Bitmap dpyBuffer = nullptr;
//	Point viewPosCached{ -1,-1 };
//	Dim dpyX = 0, dpyY = 0;
//	Rect viewWin;
//	Rect displayArea;
//};
//#define MAX_VIEWS 4
//ViewData views[MAX_VIEWS];
//// refined to accept everything from 'view' parameter
//void TileTerrainDisplay(TileMap *map, Bitmap dest, ViewData &view);
//void DisplayTerrain(TileMap *map) {
//	for (auto i = 0; i < MAX_VIEWS; ++i)
//		TileTerrainDisplay(
//			map,
//			GetBackBuffer(),
//			views[i]
//		);
//}


//int GetMapPixelWidth(void);
//int GetMapPixelHeight(void);
//void Scroll(Rect *viewWin, int dx, int dy)
//{
//	viewWin->x += dx; viewWin->y += dy;
//}
//bool CanScrollHoriz(const Rect &viewWin, int dx) {
//	return viewWin.x >= -dx &&
//		(viewWin.x + viewWin.w + dx) <= GetMapPixelWidth();
//}
//bool CanScrollVert(const Rect &viewWin, int dy) {
//	return viewWin.y >= -dy &&
//		(viewWin.y + viewWin.h + dy) <= GetMapPixelHeight();
//}
//static void FilterScrollDistance(
//	int viewStartCoord, // x or y
//	int viewSize, // w or h
//	int *d, // dx or dy
//	int maxMapSize // w or h 
//) {
//	auto val = *d + viewStartCoord;
//	if (val < 0)
//		*d = viewStartCoord; // cross low bound
//	else
//		if (viewSize >= maxMapSize)// fits entirely
//			*d = 0;
//		else
//			if ((val + viewSize) >= maxMapSize) // cross upper bound
//				*d = maxMapSize - (viewStartCoord + viewSize);
//}
//void FilterScroll(const Rect &viewWin, int *dx, int *dy) {
//	FilterScrollDistance(
//		viewWin.x, viewWin.w, dx, GetMapPixelWidth()
//	);
//	FilterScrollDistance(
//		viewWin.y, viewWin.h, dy, GetMapPixelHeight()
//	);
//}
#endif
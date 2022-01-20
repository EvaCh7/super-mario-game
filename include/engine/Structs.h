#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#define MAX_WIDTH	1024
#define MAX_HEIGHT	256

typedef unsigned char		byte;
typedef ALLEGRO_BITMAP		Bitmap;
typedef ALLEGRO_DISPLAY		Display;
typedef unsigned char		Index;
typedef Index				TileMap[MAX_WIDTH][MAX_HEIGHT];

class Rect {
public:
	int x, y, w, h;

	Rect(int, int, int, int);
};

class Point {
public:
	int x, y;

	Point(int xx, int yy);
};
#endif
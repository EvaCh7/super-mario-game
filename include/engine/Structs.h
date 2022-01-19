#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

typedef ALLEGRO_BITMAP		Bitmap;
typedef ALLEGRO_DISPLAY		Display;

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
#include <allegro5/allegro.h>
#include "DisplayTools.h"

void Blit(Bitmap *dest, unsigned int destX, unsigned int destY, Bitmap *src, unsigned int srcX, unsigned int srcY, unsigned int width, unsigned int height) {
	al_set_target_bitmap(dest);
	al_draw_bitmap_region(src, srcX, srcY, width, height,destX, destY, 0);

	return;
}

void Blit(ALLEGRO_DISPLAY *dest, unsigned int destX, unsigned int destY, Bitmap *src, unsigned int srcX, unsigned int srcY, unsigned int width, unsigned int height) {
	al_set_target_backbuffer(dest);
	al_draw_bitmap_region(src, srcX, srcY, width, height, destX, destY, 0);
	al_flip_display();

	return;
}
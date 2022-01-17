#ifndef __DISPLAY_TOOLS_H__
#define __DISPLAY_TOOLS_H__

#include "Structs.h"

void Blit(Bitmap *dest, unsigned int destX, unsigned int destY, Bitmap *src, unsigned int srcX, unsigned int srcY, unsigned int width, unsigned int height);
void Blit(ALLEGRO_DISPLAY *dest, unsigned int destX, unsigned int destY, Bitmap *src, unsigned int srcX, unsigned int srcY, unsigned int width, unsigned int height);



#endif
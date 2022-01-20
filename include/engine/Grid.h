#ifndef __GRID_H__
#define __GRID_H__

#include "engine/Structs.h"
#include "engine/Tile.h"

#define GRID_ELEMENT_WIDTH		4
#define GRID_ELEMENT_HEIGHT		4

#define GRID_BLOCK_COLUMNS		(TILE_WIDTH / GRID_ELEMENT_WIDTH)
#define GRID_BLOCK_ROWS			(TILE_HEIGHT / GRID_ELEMENT_HEIGHT)
#define GRID_ELEMENTS_PER_TILE	(GRID_BLOCK_ROWS * GRID_BLOCK_COLUMNS)
#define GRID_MAX_HEIGHT			(MAX_HEIGHT * GRID_BLOCK_ROWS)
#define GRID_MAX_WIDTH			(MAX_WIDTH * GRID_BLOCK_COLUMNS)


using GridIndex = byte;
typedef GridIndex		GridMap[GRID_MAX_WIDTH][GRID_MAX_HEIGHT];

#endif
#include "Map.h"
#include "json.h"

Map::Map(json jConfig) {
	ALLEGRO_BITMAP *bm = al_load_bitmap(std::string(jConfig["tiles"]["path"]).c_str());

	int height = jConfig["tiles"]["height"];
    int width = jConfig["tiles"]["width"];
	int counter = 0;
	for (int i = 0; i < al_get_bitmap_height(bm) / height; ++i) {
		for (int j = 0; j < al_get_bitmap_width(bm) / width; ++j) {
			this->mTiles.insert({ counter, al_create_sub_bitmap(bm, j * height, i * width, height, width) });
			counter++;
		}
	}



}

std::map<int, Bitmap *> Map::GetTiles() {
	return this->mTiles;
}
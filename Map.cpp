#include "Map.h"
#include "json.h"
#include <fstream>
#include "csv_parser.h"

Map::Map(json jConfig) {
	ALLEGRO_BITMAP *bm = al_load_bitmap(std::string(jConfig["tiles"]["path"]).c_str());

	this->iTileHeight = jConfig["tiles"]["height"];
    this->iTileWidth = jConfig["tiles"]["width"];
	int counter = 0;
	for (int i = 0; i < al_get_bitmap_height(bm) / this->iTileHeight; ++i) {
		for (int j = 0; j < al_get_bitmap_width(bm) / this->iTileWidth; ++j) {
			this->mTiles.insert({ counter, al_create_sub_bitmap(bm, j * this->iTileHeight, i * this->iTileWidth, this->iTileHeight, this->iTileWidth) });
			counter++;
		}
	}

	this->bMap = al_create_bitmap(100 * iTileWidth, 100 * iTileHeight);
	json jMaps = jConfig["map"];
	for (auto& itMap : jMaps) {
		this->DrawTilemapToMap(this->bMap, itMap["path"]);
	}
}

void Map::DrawTilemapToMap(Bitmap *bTarget, std::string sTilemapPath) {
	CSVParser csvp;
	csvp.CsvFileToBitmap(sTilemapPath);
	std::ifstream _file(sTilemapPath);
	std::string index = "";
	std::cout << sTilemapPath << std::endl;
	int i = 0;
	int j = 0;
	al_set_target_bitmap(bTarget);
	while (std::getline(_file, index, ',')) {
		if (stoi(index) != -1)
		{
			al_draw_bitmap(this->mTiles[stoi(index)], this->iTileHeight * j, this->iTileWidth * i, 0);
		}

		if (index.find("\n") != std::string::npos) {
			i++;
			j = 0;
		}
		else {
			j++;
		}
	}
}

std::map<int, Bitmap *> Map::GetTiles() {
	return this->mTiles;
}

Bitmap *Map::GetMap() {
	return this->bMap;
}
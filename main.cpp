#include <iostream>
#include <fstream>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "csv_parser.h"
#include <stdlib.h>
#include <string>
#include <iterator>
#include <map>
#include "DisplayTools.h"
#include "Structs.h"
#include "Config.h"
#include "Map.h"

int main(){
	int a;
	cfg = Config();
	al_init();
	al_init_image_addon();
	al_init_font_addon();

	ALLEGRO_DISPLAY *display = al_create_display(640, 480);

	Map mFirstStage(cfg.GetConfig(cfg.GetConfig("config/game.json")["maps"][0]["cfg"]));
	for (int i = 0; i < 100; i++) {
		Blit(display, 0, 0, mFirstStage.GetMap(), 0 + i * 16, 100 * 16 - 480, 640, 480);
		al_rest(0.1);
	}

	al_destroy_display(display);
	std::cin >> a;
	return 0;
}
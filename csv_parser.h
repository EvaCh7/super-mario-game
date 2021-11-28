#ifndef __CSV_PARSER__
#define __CSV_PARSER__

#include <iostream>
#include <fstream>
#include <string>
#include <allegro5/allegro.h>
using namespace std;

typedef ALLEGRO_BITMAP Bitmap;

class CSVParser {
private:
	Bitmap* bitmap;
public:
	CSVParser(ifstream f);
	CSVParser();
	Bitmap* CsvFileToBitmap(string file);
	ifstream get_file(string file);


};

#endif
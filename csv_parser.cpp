#include <iostream>
#include <fstream>
#include <string>
#include <allegro5/allegro.h>
#include "csv_parser.h"


CSVParser::CSVParser(ifstream f) {
	this->bitmap = NULL;
	return;
}

CSVParser::CSVParser() {
	this->bitmap = NULL;

	return;
}

Bitmap* CSVParser::CsvFileToBitmap(string file){
	ifstream _file=get_file(file);
	string index = "";
	while (getline(_file, index, ','))
	{
		cout << index << endl;
	}
	return NULL;
}

ifstream CSVParser::get_file(string file)
{
	ifstream   MyFile(file);
	return MyFile;

}








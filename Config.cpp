#include "Config.h"
#include <iostream>
#include <fstream>
#include "json.h"

json Config::GetConfig(std::string path) {
	std::ifstream iJsonFile(path);
	json jConfig;
	iJsonFile >> jConfig;
	return jConfig;
}
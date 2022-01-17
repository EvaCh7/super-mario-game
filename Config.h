#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "json.h"
#include <iostream>

class Config {
private:



public:
	
	static json GetConfig(std::string path);


};

#endif
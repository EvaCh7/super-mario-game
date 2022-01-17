#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "json.hpp"
#include <iostream>

class Config {
private:



public:
	
	json GetConfig(std::string path);


};


#endif
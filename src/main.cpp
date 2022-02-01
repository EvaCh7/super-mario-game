#include <iostream>
#include <fstream>
#include <stdio.h>
#include "game/App.h"

SuperMario* gApp;

int main(){
	SuperMario smApp;
	gApp = &smApp;
	smApp.Main();
	return 0;
}
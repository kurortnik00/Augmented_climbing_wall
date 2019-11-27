#pragma once
/* File config.txt:
kinectControl = true;
smashIt_targets = 6;
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Config {
	bool kinectControl;
	int smashIt_targets;
	void loadConfig();
	string font;
	int maxGameTime;
};


#include "testConfig.h"


void Config::loadConfig() {
	ifstream fin("config.txt");
	string line;
	while (getline(fin, line)) {
		istringstream sin(line.substr(line.find("=") + 1));
		if (line.find("kinectControl") != -1)
			sin >> Config::kinectControl;
		else if (line.find("smashIt_targets") != -1)
			sin >> Config::smashIt_targets;
		else if (line.find("font") != -1)
			sin >> Config::font;
		else if (line.find("maxGameTime") != -1)
			sin >> Config::maxGameTime;

	}
}


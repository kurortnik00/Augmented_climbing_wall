#include "Labyrinth_config.h"


void Labyrinth::Config::loadConfig() {
	ifstream fin("Labyrinth/Labyrinth_config.txt");
	string line;
	while (getline(fin, line)) {
		istringstream sin(line.substr(line.find("=") + 1));
		
		if (line.find("level1_line1_pos_x") != -1)
			sin >> Config::level1_line1_pos.x;
		else if (line.find("level1_line1_pos_y") != -1)
			sin >> Config::level1_line1_pos.y;
		else if (line.find("level1_line1_length") != -1)
			sin >> Config::level1_line1_length;
		else if (line.find("level1_line1_angl") != -1)
			sin >> Config::level1_line1_angl;
		if (line.find("level1_startButton_x") != -1)
			sin >> Config::level1_startButton.x;
		else if (line.find("level1_startButton_y") != -1)
			sin >> Config::level1_startButton.y;
		else if (line.find("level1_winButton_x") != -1)
			sin >> Config::level1_winButton.x;
		else if (line.find("level1_winButton_y") != -1)
			sin >> Config::level1_winButton.y;
		
	}
}


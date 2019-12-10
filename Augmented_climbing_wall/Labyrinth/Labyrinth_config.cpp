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
		else if (line.find("level1_startButton_radius") != -1)
			sin >> Config::level1_startButton_radius;
		else if (line.find("level1_winButton_x") != -1)
			sin >> Config::level1_winButton.x;
		else if (line.find("level1_winButton_y") != -1)
			sin >> Config::level1_winButton.y;
		else if (line.find("level1_winButton_radius") != -1)
			sin >> Config::level1_winButton_radius;

		if (line.find("level2_line1_pos_x") != -1)
			sin >> Config::level2_line1_pos.x;
		else if (line.find("level2_line1_pos_y") != -1)
			sin >> Config::level2_line1_pos.y;
		else if (line.find("level2_line1_length") != -1)
			sin >> Config::level2_line1_length;
		else if (line.find("level2_line1_angl") != -1)
			sin >> Config::level2_line1_angl;
		else if(line.find("level2_line2_pos_x") != -1)
			sin >> Config::level2_line2_pos.x;
		else if (line.find("level2_line2_pos_y") != -1)
			sin >> Config::level2_line2_pos.y;
		else if (line.find("level2_line2_length") != -1)
			sin >> Config::level2_line2_length;
		else if (line.find("level2_line2_angl") != -1)
			sin >> Config::level2_line2_angl;
		if (line.find("level2_startButton_x") != -1)
			sin >> Config::level2_startButton.x;
		else if (line.find("level2_startButton_y") != -1)
			sin >> Config::level2_startButton.y;
		else if (line.find("level2_startButton_radius") != -1)
			sin >> Config::level2_startButton_radius;
		else if (line.find("level2_winButton_x") != -1)
			sin >> Config::level2_winButton.x;
		else if (line.find("level2_winButton_y") != -1)
			sin >> Config::level2_winButton.y;
		else if (line.find("level2_winButton_radius") != -1)
			sin >> Config::level2_winButton_radius;


		if (line.find("level3_line1_pos_x") != -1)
			sin >> Config::level3_line1_pos.x;
		else if (line.find("level3_line1_pos_y") != -1)
			sin >> Config::level3_line1_pos.y;
		else if (line.find("level3_line1_length") != -1)
			sin >> Config::level3_line1_length;
		else if (line.find("level3_line1_angl") != -1)
			sin >> Config::level3_line1_angl;
		else if (line.find("level3_line2_pos_x") != -1)
			sin >> Config::level3_line2_pos.x;
		else if (line.find("level3_line2_pos_y") != -1)
			sin >> Config::level3_line2_pos.y;
		else if (line.find("level3_line2_length") != -1)
			sin >> Config::level3_line2_length;
		else if (line.find("level3_line2_angl") != -1)
			sin >> Config::level3_line2_angl;
		if (line.find("level3_startButton_x") != -1)
			sin >> Config::level3_startButton.x;
		else if (line.find("level3_startButton_y") != -1)
			sin >> Config::level3_startButton.y;
		else if (line.find("level3_startButton_radius") != -1)
			sin >> Config::level3_startButton_radius;
		else if (line.find("level3_winButton_x") != -1)
			sin >> Config::level3_winButton.x;
		else if (line.find("level3_winButton_y") != -1)
			sin >> Config::level3_winButton.y;
		else if (line.find("level3_winButton_radius") != -1)
			sin >> Config::level3_winButton_radius;
		else if (line.find("level3_angVel") != -1)
			sin >> Config::level3_angVel;


		if (line.find("level4_line1_pos_x") != -1)
			sin >> Config::level4_line1_pos.x;
		else if (line.find("level4_line1_pos_y") != -1)
			sin >> Config::level4_line1_pos.y;
		else if (line.find("level4_line1_length") != -1)
			sin >> Config::level4_line1_length;
		else if (line.find("level4_line1_angl") != -1)
			sin >> Config::level4_line1_angl;
		else if (line.find("level4_line2_pos_x") != -1)
			sin >> Config::level4_line2_pos.x;
		else if (line.find("level4_line2_pos_y") != -1)
			sin >> Config::level4_line2_pos.y;
		else if (line.find("level4_line2_length") != -1)
			sin >> Config::level4_line2_length;
		else if (line.find("level4_line2_angl") != -1)
			sin >> Config::level4_line2_angl;
		else if (line.find("level4_line3_pos_x") != -1)
			sin >> Config::level4_line3_pos.x;
		else if (line.find("level4_line3_pos_y") != -1)
			sin >> Config::level4_line3_pos.y;
		else if (line.find("level4_line3_length") != -1)
			sin >> Config::level4_line3_length;
		else if (line.find("level4_line3_angl") != -1)
			sin >> Config::level4_line3_angl;
		else if (line.find("level4_line4_pos_x") != -1)
			sin >> Config::level4_line4_pos.x;
		else if (line.find("level4_line4_pos_y") != -1)
			sin >> Config::level4_line4_pos.y;
		else if (line.find("level4_line4_length") != -1)
			sin >> Config::level4_line4_length;
		else if (line.find("level4_line4_angl") != -1)
			sin >> Config::level4_line4_angl;
		else if (line.find("level4_line5_pos_x") != -1)
			sin >> Config::level4_line5_pos.x;
		else if (line.find("level4_line5_pos_y") != -1)
			sin >> Config::level4_line5_pos.y;
		else if (line.find("level4_line5_length") != -1)
			sin >> Config::level4_line5_length;
		else if (line.find("level4_line5_angl") != -1)
			sin >> Config::level4_line5_angl;
		if (line.find("level4_startButton_x") != -1)
			sin >> Config::level4_startButton.x;
		else if (line.find("level4_startButton_y") != -1)
			sin >> Config::level4_startButton.y;
		else if (line.find("level4_startButton_radius") != -1)
			sin >> Config::level4_startButton_radius;
		else if (line.find("level4_winButton_x") != -1)
			sin >> Config::level4_winButton.x;
		else if (line.find("level4_winButton_y") != -1)
			sin >> Config::level4_winButton.y;
		else if (line.find("level4_winButton_radius") != -1)
			sin >> Config::level4_winButton_radius;
		else if (line.find("level4_button1_x") != -1)
			sin >> Config::level4_button1.x;
		else if (line.find("level4_button1_y") != -1)
			sin >> Config::level4_button1.y;
		else if (line.find("level4_button1_radius") != -1)
			sin >> Config::level4_button1_radius;
		else if (line.find("level4_button2_x") != -1)
			sin >> Config::level4_button2.x;
		else if (line.find("level4_button2_y") != -1)
			sin >> Config::level4_button2.y;
		else if (line.find("level4_button2_radius") != -1)
			sin >> Config::level4_button2_radius;
		else if (line.find("level4_anglVel") != -1)
			sin >> Config::level4_anglVel;	
		else if (line.find("level4_timeToSwithOn_blinkLine") != -1)
			sin >> Config::level4_timeToSwithOn_blinkLine;
		else if (line.find("level4_timeToSwithOff_blinkLine") != -1)
			sin >> Config::level4_timeToSwithOff_blinkLine;
		else if (line.find("level4_vel") != -1)
			sin >> Config::level4_vel;

		else if (line.find("level5_vel_x") != -1)
			sin >> Config::level5_vel.x;
		else if (line.find("level5_vel_y") != -1)
			sin >> Config::level5_vel.y;
		else if (line.find("level5_radius") != -1)
			sin >> Config::level5_radius;
		else if (line.find("level5_pos_x") != -1)
			sin >> Config::level5_pos.x;
		else if (line.find("level5_pos_y") != -1)
			sin >> Config::level5_pos.y;
		else if (line.find("level5_teslaParticls") != -1)
			sin >> Config::level5_teslaParticls;
		if (line.find("level5_startButton_x") != -1)
			sin >> Config::level5_startButton.x;
		else if (line.find("level5_startButton_y") != -1)
			sin >> Config::level5_startButton.y;
		else if (line.find("level5_startButton_radius") != -1)
			sin >> Config::level5_startButton_radius;
		else if (line.find("level5_winButton_x") != -1)
			sin >> Config::level5_winButton.x;
		else if (line.find("level5_winButton_y") != -1)
			sin >> Config::level5_winButton.y;
		else if (line.find("level5_winButton_radius") != -1)
			sin >> Config::level5_winButton_radius;
		else if (line.find("level5_angVel") != -1)
			sin >> Config::level5_anglVel;


	
	}
}


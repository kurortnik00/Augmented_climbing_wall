#pragma once
/* File config.txt:
kinectControl = true;
smashIt_targets = 6;
*/
#include "../stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

namespace Labyrinth
{
	struct Config {

		void loadConfig();
		string font;


		sf::Vector2f level1_line1_pos;
		int level1_line1_length;
		int level1_line1_angl;
		sf::Vector2f level1_startButton;
		float level1_startButton_radius;
		sf::Vector2f level1_winButton;
		float level1_winButton_radius;


		sf::Vector2f level2_line1_pos;
		int level2_line1_length;
		int level2_line1_angl;
		sf::Vector2f level2_line2_pos;
		int level2_line2_length;
		int level2_line2_angl;
		sf::Vector2f level2_startButton;
		float level2_startButton_radius;
		sf::Vector2f level2_winButton;
		float level2_winButton_radius;

		sf::Vector2f level3_line1_pos;
		int level3_line1_length;
		int level3_line1_angl;
		sf::Vector2f level3_line2_pos;
		int level3_line2_length;
		int level3_line2_angl;
		sf::Vector2f level3_startButton;
		float level3_startButton_radius;
		sf::Vector2f level3_winButton;
		float level3_winButton_radius;
		int level3_angVel;

		sf::Vector2f level4_line1_pos;
		int level4_line1_length;
		int level4_line1_angl;
		sf::Vector2f level4_line2_pos;
		int level4_line2_length;
		int level4_line2_angl;
		sf::Vector2f level4_line3_pos;
		int level4_line3_length;
		int level4_line3_angl;
		sf::Vector2f level4_line4_pos;
		int level4_line4_length;
		int level4_line4_angl;
		sf::Vector2f level4_line5_pos;
		int level4_line5_length;
		int level4_line5_angl;
		sf::Vector2f level4_startButton;
		float level4_startButton_radius;
		sf::Vector2f level4_winButton;
		float level4_winButton_radius;
		sf::Vector2f level4_button1;
		float level4_button1_radius;
		sf::Vector2f level4_button2;
		float level4_button2_radius;
		int level4_timeToSwithOn_blinkLine;
		int	level4_timeToSwithOff_blinkLine;
		int level4_anglVel;
		int	level4_vel;

		sf::Vector2f level5_vel;
		int	level5_radius;
		sf::Vector2f level5_pos;
		int	level5_teslaParticls;
		sf::Vector2f level5_startButton;
		float level5_startButton_radius;
		sf::Vector2f level5_winButton;
		float level5_winButton_radius;
		int level5_anglVel;

	};
}


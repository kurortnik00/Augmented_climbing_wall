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
		sf::Vector2f level1_winButton;


		sf::Vector2f level2_line1_pos;
		int level2_line1_length;
		int level2_line1_angl;
		sf::Vector2f level2_line2_pos;
		int level2_line2_length;
		int level2_line2_angl;
		sf::Vector2f level2_startButton;
		sf::Vector2f level2_winButton;

		sf::Vector2f level3_line1_pos;
		int level3_line1_length;
		int level3_line1_angl;
		sf::Vector2f level3_line2_pos;
		int level3_line2_length;
		int level3_line2_angl;
		sf::Vector2f level3_startButton;
		sf::Vector2f level3_winButton;
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
		sf::Vector2f level4_winButton;
		sf::Vector2f level4_button1;
		sf::Vector2f level4_button2;
		int level4_timeToSwithOn_blinkLine;
		int	level4_timeToSwithOff_blinkLine;
		int level4_anglVel;
		int	level4_vel;

		int	level5_vel;
		int	level5_radius;
		sf::Vector2f level5_pos;
		int	level5_teslaParticls;

	};
}


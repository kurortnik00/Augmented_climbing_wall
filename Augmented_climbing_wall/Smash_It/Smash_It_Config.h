#pragma once

#include "../stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

namespace Smash_It
{
	static struct Config {
		static bool kinectControl;
		static int smashIt_targets;
		static void loadConfig(std::string path);
		static string font;
		static int maxGameTime;
		static sf::Vector2f game_over_text_pos;
		static float  game_over_text_size;
		static sf::Vector2f game_over_score_pos;
		static float  game_over_score_size;
		static sf::Vector2f restart_pos;
		static float restart_scale;
		static float restart_itarationRadius_scale;
		static sf::Vector2f targets_vel;
		static float targets_itaractionRadius;

	};
}




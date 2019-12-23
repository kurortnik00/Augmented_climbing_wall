#pragma once

#include <SFML/Graphics.hpp>

namespace Territory
{
	namespace Config
	{
		// General
		extern float fps;
		extern float game_length;
		extern float screen_width, screen_height;
		extern bool kinectControl;
		extern sf::Uint32 window_mode;

		// Colors
		extern sf::Color red;				// Color of the left player
		extern sf::Color green;				// Color of the right player

		// Resources
		extern std::string texture_left_hand_path;	// Path to left hand texture
		extern std::string texture_right_hand_path;	// Path to right hand texture
	}
}
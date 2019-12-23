#include "Territory_config.hpp"

namespace Territory
{
	namespace Config
	{
		// General
		float fps = 120.f;
		float screen_width = 800.f;
		float screen_height = 600.f;
		bool kinectControl = false;
		sf::Uint32 window_mode = sf::Style::Fullscreen;

		// Colors
		sf::Color red = sf::Color(204, 0, 0);
		sf::Color green = sf::Color(0, 102, 0);

		// Resources
		std::string texture_left_hand_path = "territory/media/textures/left_hand.png";
		std::string texture_right_hand_path = "territory/media/textures/right_hand.png";
	}
}
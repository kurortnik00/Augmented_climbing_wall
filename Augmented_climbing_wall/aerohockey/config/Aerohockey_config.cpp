#include <fstream>
#include <sstream>
#include <string>

#include "Aerohockey_config.hpp"
#include "../../mainWindow.h"

namespace Aerohockey
{
	namespace Config
	{
		// General
		float fps = 120.f;
		float screen_width = MainWindow::SCREEN_WIDTH;
		float screen_height = MainWindow::SCREEN_HEIGHT;
		bool kinectControl = false;
		sf::Uint32 window_mode = sf::Style::Fullscreen;

		// Game settings
		unsigned max_score = 5;
		float game_length = 180.f;
		float game_start_delay = 2.f;

		// Result view settings
		float result_demonstration_time = 7.f;
		float result_border_velocity = 400.f;
		float result_sign_delay = 2.f;

		// Colors
		sf::Color red = sf::Color(204, 0, 0);
		sf::Color green = sf::Color(0, 102, 0);
		sf::Color trace_color = sf::Color(243, 240, 240, 64);

		// Puck
		bool use_velocity_cap = true;
		float max_puck_velocity = 800.f;
		float initial_puck_velocity = 400.f;
		float puck_radius = screen_height / 20.f;
		int trace_capacity = 20;
		float trace_min_radius = 10.f;

		// Paddles
		float paddle_radius = screen_height / 20.f;

		// Collisions
		bool use_paddle_velocity = true;

		// Ready buttons
		float left_ready_button_position_x = screen_width / 4;
		float left_ready_button_position_y = screen_height / 2;
		float left_ready_button_size_x = screen_width / 10;
		float left_ready_button_size_y = screen_width / 10;
		float right_ready_button_position_x = screen_width * 3 / 4;
		float right_ready_button_position_y = screen_height / 2;
		float right_ready_button_size_x = screen_width / 10;
		float right_ready_button_size_y = screen_width / 10;

		// Scoreboard
		bool top_position = true;
		int font_size = 60;
		float timer_width = 180.f;
		float score_width = 90.f;
		float board_height = 90.f;

		// Resources
		std::string font_result_path = "aerohockey/media/fonts/DINPro-Black.ttf";
		std::string font_scoreboard_path = "aerohockey/media/fonts/DIN.ttf";
		std::string sound_scored_path = "aerohockey/media/sounds/scored.wav";
		std::string sound_hit_path = "aerohockey/media/sounds/hit.wav";
		std::string sound_wall_path = "aerohockey/media/sounds/wall.wav";
		std::string texture_background_path = "aerohockey/media/textures/background.jpg";
		std::string texture_puck_path = "aerohockey/media/textures/puck.png";
		std::string texture_left_hand_path = "aerohockey/media/textures/left_hand.png";
		std::string texture_right_hand_path = "aerohockey/media/textures/right_hand.png";


		template <typename T>
		void read_param(std::string& line, std::string name, T& value)
		{
			std::istringstream sin(line.substr(line.find("=") + 1));
			if (line.find(name) != -1)
			{
				sin >> value;
				std::cout << name << ": " << value << "\n";
			}
		}


		void load(std::string path)
		{
			// Open file if exists
			std::ifstream input(path);
			if (input.fail())
			{
				std::cout << "Failed to open config file: " << path << "\n";
				return;
			}

			std::cout << "Loading config from: " << path << "\n";

			// Read lines
			std::string line;
			while (std::getline(input, line))
			{
				// Comment lines should start with #
				if (line[0] == '#')
				{
					continue;
				}

				read_param(line, "fps", Config::fps);
				read_param(line, "screen_width", Config::screen_width);
				read_param(line, "screen_height", Config::screen_height);
				read_param(line, "kinectControl", Config::kinectControl);

				read_param(line, "max_score", Config::max_score);
				read_param(line, "game_length", Config::game_length);
				read_param(line, "result_demonstration_time", Config::result_demonstration_time);

				read_param(line, "use_velocity_cap", Config::use_velocity_cap);
				read_param(line, "max_puck_velocity", Config::max_puck_velocity);
				read_param(line, "initial_puck_velocity", Config::initial_puck_velocity);
				read_param(line, "puck_radius", Config::puck_radius);
				read_param(line, "trace_capacity", Config::trace_capacity);
				read_param(line, "trace_min_radius", Config::trace_min_radius);

				read_param(line, "paddle_radius", Config::paddle_radius);

				read_param(line, "use_paddle_velocity", Config::use_paddle_velocity);

				read_param(line, "left_ready_button_position_x", Config::left_ready_button_position_x);
				read_param(line, "left_ready_button_position_y", Config::left_ready_button_position_y);
				read_param(line, "left_ready_button_size_x", Config::left_ready_button_size_x);
				read_param(line, "left_ready_button_size_y", Config::left_ready_button_size_y);
				read_param(line, "right_ready_button_position_x", Config::right_ready_button_position_x);
				read_param(line, "right_ready_button_position_y", Config::right_ready_button_position_y);
				read_param(line, "right_ready_button_size_x", Config::right_ready_button_size_x);
				read_param(line, "right_ready_button_size_y", Config::right_ready_button_size_y);
				
				read_param(line, "top_position", Config::top_position);
				read_param(line, "font_size", Config::font_size);
				read_param(line, "timer_width", Config::timer_width);
				read_param(line, "score_width", Config::score_width);
				read_param(line, "board_height", Config::board_height);

				read_param(line, "font_scoreboard_path", Config::font_scoreboard_path);
				read_param(line, "sound_scored_path", Config::sound_scored_path);
				read_param(line, "sound_hit_path", Config::sound_hit_path);
				read_param(line, "sound_wall_path", Config::sound_wall_path);
				read_param(line, "texture_background_path", Config::texture_background_path);
				read_param(line, "texture_puck_path", Config::texture_puck_path);
				read_param(line, "texture_left_hand_path", Config::texture_left_hand_path);
				read_param(line, "texture_right_hand_path", Config::texture_right_hand_path);
			}
		}
	}
}
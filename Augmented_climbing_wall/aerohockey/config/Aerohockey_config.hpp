#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace Aerohockey
{
	namespace Config
	{
		// General
		extern float fps;
		extern float game_length;
		extern float screen_width, screen_height;
		extern bool kinectControl;
		extern sf::Uint32 window_mode;

		// Game settings
		extern unsigned max_score;				// Scoring max_score times ends the game
		extern float game_length;				// Game length (in seconds)
		extern float game_start_delay;			// Delay for players to prepare

		// Result view settings
		extern float result_demonstration_time; // Result demonstration time after game ends (in seconds)
		extern float result_border_velocity;	// Velocity of the border of rectangles in result view
		extern float result_sign_delay;			// Little delay before sign appears

		// Colors
		extern sf::Color red;					// Color of the left player
		extern sf::Color green;					// Color of the right player
		extern sf::Color trace_color;			// Color of the puck trace

		// Puck
		extern bool use_velocity_cap;			// If true, then puck speed is always <= max_velocity_cap
		extern float max_puck_velocity;			// Upper limit for puck speed if use_velocity_cap is true
		extern float initial_puck_velocity;		// Initial puck velocity when game starts or goal was scored
		extern float puck_radius;				// Radius of the puck
		extern int trace_capacity;				// Number of previous positions used to show trace
		extern float trace_min_radius;			// Radius of the smallest trace piece

		// Paddles
		extern float paddle_radius;				// Radius of paddles

		// Collisions
		extern bool use_paddle_velocity;		// If true, then paddle velocity is used in collision physics
												// If false, paddle velocity is 0 during collision processing

		// Ready buttons
		extern float left_ready_button_position_x;			// Position of the left ready button (X-axis)
		extern float left_ready_button_position_y;			// Position of the left ready button (Y-axis)
		extern float left_ready_button_size_x;				// Size of the left ready button (X-axis)
		extern float left_ready_button_size_y;				// Size of the left ready button (Y-axis)
		extern float right_ready_button_position_x;			// Position of the right ready button (X-axis)
		extern float right_ready_button_position_y;			// Position of the right ready button (Y-axis)
		extern float right_ready_button_size_x;				// Size of the right ready button (X-axis)
		extern float right_ready_button_size_y;				// Size of the right ready button (Y-axis)

		// Scoreboard
		extern bool top_position;					// If true, then board is at top of the screen, otherwise at bottom
		extern int font_size;						// Font size
		extern float timer_width;					// Timer cell width in pixels
		extern float score_width;					// Score cell width in pixels
		extern float board_height;					// Scoreboard height in pixels

		// Resources
		extern std::string font_result_path;		// Path to font for results
		extern std::string font_scoreboard_path;	// Path to font for scoreboard
		extern std::string sound_scored_path;		// Path to 'scored' sound
		extern std::string sound_hit_path;			// Path to 'hit' sound
		extern std::string sound_wall_path;			// Path to 'wall' sound
		extern std::string texture_background_path;	// Path to background texture
		extern std::string texture_puck_path;		// Path to puck texture
		extern std::string texture_left_hand_path;	// Path to left hand texture
		extern std::string texture_right_hand_path;	// Path to right hand texture

		// Loader function
		void load(std::string path);
	}
}

#endif /* end of include guard: CONFIG_HPP */

#include "Smash_It_Config.h"



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


void Smash_It::Config::loadConfig(std::string path)
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

		read_param(line, "smashIt_targets", Config::smashIt_targets);
		read_param(line, "font", Config::font);
		read_param(line, "maxGameTime", Config::maxGameTime);


		read_param(line, "mgame_over_text_pos_x", Config::game_over_text_pos.x);
		read_param(line, "game_over_text_pos_y", Config::game_over_text_pos.y);
		read_param(line, "game_over_text_size", Config::game_over_text_size);
		read_param(line, "game_over_score_pos_x", Config::game_over_score_pos.x);
		read_param(line, "game_over_score_pos_y", Config::game_over_score_pos.y);
		read_param(line, "game_over_score_size", Config::game_over_score_size);
		read_param(line, "restart_pos_x", Config::restart_pos.x);
		read_param(line, "restart_pos_y", Config::restart_pos.y);
		read_param(line, "restart_scale", Config::restart_scale);
		read_param(line, "restart_itarationRadius_scale", Config::restart_itarationRadius_scale);
		read_param(line, "targets_vel_x", Config::targets_vel.x);
		read_param(line, "targets_vel_y", Config::targets_vel.y);
		read_param(line, "targets_itaractionRadius", Config::targets_itaractionRadius);
		
	}
}

bool Smash_It::Config::kinectControl;
int Smash_It::Config::smashIt_targets;
string Smash_It::Config::font;
int Smash_It::Config::maxGameTime;
sf::Vector2f Smash_It::Config::game_over_text_pos;
float  Smash_It::Config::game_over_text_size;
sf::Vector2f Smash_It::Config::game_over_score_pos;
float  Smash_It::Config::game_over_score_size;
sf::Vector2f Smash_It::Config::restart_pos;
float Smash_It::Config::restart_scale;
float Smash_It::Config::restart_itarationRadius_scale;
sf::Vector2f Smash_It::Config::targets_vel;
float Smash_It::Config::targets_itaractionRadius;



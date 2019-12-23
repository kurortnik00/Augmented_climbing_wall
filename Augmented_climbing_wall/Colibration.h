#pragma once
#include "Cliker.h"
#include "server.h"
#include <iostream>
#include <fstream>

class Colibration
{
public:
	static void autoColibration();
	static void manualAdditionalColibration(myServer& server);
	static void init();

private:

	static std::vector<float> x_sum_vector;
	static std::vector<float> y_sum_vector;
	static std::vector<float> x_mult_vector;
	static std::vector<float> y_mult_vector;

	static std::vector<float> x_error;
	static std::vector<float> y_error;

	static float x_averError;
	static float y_averError;


	static sf::CircleShape shape;
	static float radius;

	static enum colibrationCorners
	{
		LEFT_TOP, LEFT_BOTTOM, RIGHT_TOP, RIGHT_BOTTOM, END
	};
	static colibrationCorners corner;
	static sf::Clock clock;
	static sf::Clock vectorClock;
	static sf::Font font;

	

	enum additionColibrationButtons
	{
		x_translation_up,
		x_translation_down,
		y_translation_up,
		y_translation_down,
		
	};
	static std::vector<sf::Vector2f> additionalValueColibration(std::vector<sf::Vector2f> limbsAditionValues, myServer& server);
};


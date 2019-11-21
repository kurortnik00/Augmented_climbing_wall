#pragma once
#include "stdafx.h"

class MainWindow
{
public:
	static sf::RenderWindow &getWindow();

	static float SCREEN_WIDTH;
	static float SCREEN_HEIGHT;
private:
	static sf::RenderWindow window;
};


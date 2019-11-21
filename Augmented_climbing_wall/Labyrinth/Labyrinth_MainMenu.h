#pragma once
#include "../stdafx.h"
#include <list>

namespace Labyrinth
{
	class MainMenu
	{

	public:
		enum MenuResult { Nothing, Exit, Play, PreviousLevel, NextLevel };


		struct MenuItem
		{
		public:
			sf::Rect<int> rect;
			MenuResult  action;

		};

		MenuResult Show(sf::RenderWindow& window);

	private:
		MenuResult GetMenuResponse(sf::RenderWindow& window);
		MenuResult HandleClick(int x, int y);
		std::list<MenuItem> _menuItems;
	};
}

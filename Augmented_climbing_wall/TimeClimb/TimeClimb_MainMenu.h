#pragma once
#include "../stdafx.h"
#include <sstream>
#include <iomanip>
#include <list>
#include <sstream>
#include "../server.h"
#include "../Cliker.h"

namespace TimeClimb
{
	class MainMenu
	{

	public:
		enum MenuResult { Nothing, Exit, Play, Score_board, Custom };

		struct MenuItem
		{
		public:
			MenuItem(sf::Vector2f position, MenuResult action);
			void Move(sf::Vector2f pos);
			sf::Vector2f _position;
			sf::Rect<int> rect;
			sf::Texture _texture;
			sf::Sprite _sprite;
			float animationTime;
			sf::Clock animationClock;
			int animationFrame;
			sf::Font font;
			sf::Text text;
			sf::Vector2f _center;
			MenuResult _action;
			float _radius;
		};


		MenuResult Show(sf::RenderWindow& window, std::set<std::pair<float, std::string>>& TOP_List, myServer& server);
		void Update(sf::RenderWindow& window);
		float dist2(sf::Vector2f const & p1, sf::Vector2f const & p2);
		void Draw(sf::RenderWindow& window);

	private:
		MenuResult GetMenuResponse(sf::RenderWindow& window, myServer& server);
		MenuResult HandleClick(sf::RenderWindow& window, int x, int y);
		std::list<MenuItem> _menuItems;
		int k = 0;
		sf::Sprite sprite;
		sf::Vector2f velocity;
		sf::Clock serverDelayClock;
	};
}

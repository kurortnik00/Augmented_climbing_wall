#pragma once
#include "../stdafx.h"
#include "TimeClimb_GameObjectManager.h"
#include "TimeClimb_Target.h"

namespace TimeClimb
{
	class CustomScreen
	{
	public:
		CustomScreen();
		~CustomScreen();

		sf::Vector2f Show(sf::RenderWindow& window, GameObjectManager& gameObjectManager);

	private:
		//sf::Vector2f HandleClick(int x, int y);
		sf::Sprite  _sprite;
		sf::Texture _texture;
		sf::Image _image;

	};
}


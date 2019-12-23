#pragma once

#include "Territory_paddle.hpp"

namespace Territory
{
	struct ReadyButton
	{
		ReadyButton(sf::Vector2f position, sf::Vector2f size);
		bool isActivated();
		void setTexture(sf::Texture& texture);
		sf::Sprite& sprite();
		void update(std::vector<Paddle> paddles);

	private:
		sf::Vector2f position_, size_;
		sf::Sprite sprite_;
		bool activated = false;
	};
}
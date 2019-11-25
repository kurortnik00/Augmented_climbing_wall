#pragma once
#include "../StdAfx.h"
#include "Smash_It_Game.h"
#include <random>
#include "Smash_It_VisibleGameObject.h"
#include "../BodyBasics.h"
#include "Kinect.h"

namespace Smash_It
{
	class Target :
		public VisibleGameObject
	{
	public:
		Target();
		~Target();

		void Update(sf::Event& event);
		bool getState();
		bool getClickState();
		void setClickState(bool ans);
		void reInit();
		int getRandomNumber(int min, int max);
		void Draw(sf::RenderWindow & window);


	private:
		bool isActive;
		bool hasClicked;
		float spriteX, spriteY, w, h;
		void animation();
		int animationFrame;
		sf::Clock animationClock;
		bool animationStart;
		void velocityAnimation();
		sf::Clock velocityAnimationClock;
		sf::Vector2f velocity;
		int windowSizeX, windowSizeY;
		void setRandomFlyStart();
		const sf::Vector2f constVelocity;
		float velocityAnimationTime;
		float animationTime;


	};
}


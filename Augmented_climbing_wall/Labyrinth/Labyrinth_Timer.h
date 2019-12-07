#pragma once
#include "../stdafx.h"
#include "Labyrinth_VisibleGameObject.h"

namespace Labyrinth
{
	class Timer : public VisibleGameObject
	{
	public:
		Timer();
		~Timer();

		static void Load(std::string filename);
		static void Draw(sf::RenderWindow & renderWindow);
		static void Restart();
		static sf::Time GetTime();
		static void setFinished(bool res);		//переводит finished в true
		static bool getFinished();
		static void reInit();
		static bool start;
		static float gameTime;


	private:
		static sf::Clock gameTimeClock;
		static sf::Time t1;
		static sf::Font font;
		static sf::Text text;
		static bool finished;
		static 	float finishedTime;
		
	};
}


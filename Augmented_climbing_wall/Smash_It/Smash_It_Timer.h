#pragma once
#include "../stdafx.h"
#include "Smash_It_VisibleGameObject.h"

namespace Smash_It
{
	class Timer : public VisibleGameObject
	{
	public:
		Timer();
		~Timer();

		void Load(std::string filename);
		void Draw(sf::RenderWindow & renderWindow);
		void Restart();
		sf::Time GetTime();
		void setFinished(bool res);		//переводит finished в true
		bool getFinished();
		void reInit();
		float getFinishedTime();


	private:
		sf::Clock gameTimeClock;
		sf::Time t1;
		sf::Font font;
		sf::Text text;
		bool finished;
		float finishedTime;
	};
}


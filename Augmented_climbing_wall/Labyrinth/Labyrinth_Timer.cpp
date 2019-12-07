#include "Labyrinth_Timer.h"
#include <sstream>

//Класс для отрисовки таймера и засекания времени

Labyrinth::Timer::Timer()
{
	gameTimeClock.restart();
	text.setStyle(sf::Text::Bold);
	text.setPosition(50, 400);
	finished = false;
	finishedTime = 0;
}

Labyrinth::Timer::~Timer() {

}

void Labyrinth::Timer::Load(std::string filename) {
	font.loadFromFile(filename);
}

sf::Time Labyrinth::Timer::GetTime() {
	return gameTimeClock.getElapsedTime();
}

void Labyrinth::Timer::Draw(sf::RenderWindow & renderWindow) {


	gameTime = gameTimeClock.getElapsedTime().asMilliseconds() / 1000.0;

	if (finished) {
		gameTime = finishedTime;
	}

	if (!start) {
		gameTimeClock.restart();
		gameTime = gameTimeClock.getElapsedTime().asMilliseconds() / 1000.0;
	}
	if (!finished)
	{
		std::ostringstream timerStr;
		timerStr << gameTime;
		text.setString(timerStr.str());
		renderWindow.draw(text);
	}
	
}

void Labyrinth::Timer::Restart() {
	gameTimeClock.restart();
}

void Labyrinth::Timer::setFinished(bool res)
{
	finished = res;
	finishedTime = gameTimeClock.getElapsedTime().asMilliseconds() / 1000.0;
	text.setCharacterSize(250);
	text.setPosition(500, 400);
}
bool Labyrinth::Timer::getFinished() {
	return finished;
}

void Labyrinth::Timer::reInit() {
	text.setCharacterSize(150);
	gameTimeClock.restart();
	text.setStyle(sf::Text::Bold);
	text.setPosition(50, 400);
	finished = false;
	start = false;
}
	

sf::Clock Labyrinth::Timer::gameTimeClock;
sf::Time Labyrinth::Timer::t1;
sf::Font Labyrinth::Timer::font;
sf::Text Labyrinth::Timer::text("", font, 50);
bool Labyrinth::Timer::finished;
float Labyrinth::Timer::finishedTime;
bool Labyrinth::Timer::start;
float Labyrinth::Timer::gameTime;
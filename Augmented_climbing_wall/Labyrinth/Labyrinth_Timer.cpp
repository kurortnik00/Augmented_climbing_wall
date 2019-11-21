#include "Labyrinth_Timer.h"
#include <sstream>

//Класс для отрисовки таймера и засекания времени

Labyrinth::Timer::Timer() :
	text("", font, 150)
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


	float gameTime = gameTimeClock.getElapsedTime().asMilliseconds() / 1000.0;

	if (finished) {
		gameTime = finishedTime;
	}

	if (!VisibleGameObject::getStart()) {
		gameTimeClock.restart();
		gameTime = gameTimeClock.getElapsedTime().asMilliseconds() / 1000.0;
	}
	std::ostringstream timerStr;
	timerStr << gameTime;
	text.setString(timerStr.str());
	renderWindow.draw(text);
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
	VisibleGameObject::setStart(false);
}
	
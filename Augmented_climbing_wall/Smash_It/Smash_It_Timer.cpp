#include "Smash_It_Timer.h"
#include <sstream>

//Класс для отрисовки таймера и засекания времени

Smash_It::Timer::Timer() :
	text("", font, 150)
{

	gameTimeClock.restart();
	text.setStyle(sf::Text::Bold);
	text.setPosition(20, -20);
	finished = false;
	finishedTime = 0;

	
	maxGameTime = Config::maxGameTime;
}

Smash_It::Timer::~Timer() {

}

void Smash_It::Timer::Load(std::string filename) {
	font.loadFromFile(filename);
}

sf::Time Smash_It::Timer::GetTime() {
	return gameTimeClock.getElapsedTime();
}

void Smash_It::Timer::Draw(sf::RenderWindow & renderWindow) {

	float gameTime = gameTimeClock.getElapsedTime().asMilliseconds() / 1000.0;

	if (finished) {
		gameTime = finishedTime;
	}
	
	if (gameTime > maxGameTime) setFinished(true);    ///should be in Update function

	std::ostringstream timerStr;
	timerStr << gameTime;
	text.setString(timerStr.str());
	renderWindow.draw(text);
}

void Smash_It::Timer::Restart() {
	gameTimeClock.restart();
}

void Smash_It::Timer::setFinished(bool res)
{
	finished = res;
	finishedTime = gameTimeClock.getElapsedTime().asMilliseconds() / 1000.0;
	text.setCharacterSize(250);
	text.setPosition(500, 200);
}
bool Smash_It::Timer::getFinished() {
	return finished;
}

void Smash_It::Timer::reInit() {
	text.setCharacterSize(150);
	gameTimeClock.restart();
	text.setStyle(sf::Text::Bold);
	text.setPosition(20, -20);
	finished = false;
}

float Smash_It::Timer::getFinishedTime()
{
	return finishedTime;
}
	
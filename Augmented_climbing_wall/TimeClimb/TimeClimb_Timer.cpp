#include "TimeClimb_Timer.h"
#include <sstream>

//Класс для отрисовки таймера и засекания времени

TimeClimb::Timer::Timer() :
	text("", font, 150)
{

	gameTimeClock.restart();
	text.setStyle(sf::Text::Bold);
	text.setPosition(50, 400);
	finished = false;
	finishedTime = 0;
}

TimeClimb::Timer::~Timer() {

}

void TimeClimb::Timer::Load(std::string filename) {
	font.loadFromFile(filename);
}

sf::Time TimeClimb::Timer::GetTime() {
	return gameTimeClock.getElapsedTime();
}

void TimeClimb::Timer::Draw(sf::RenderWindow & renderWindow) {

	if (VisibleGameObject::getVisible())
	{
		float gameTime = gameTimeClock.getElapsedTime().asMilliseconds() / 1000.0;

		if (finished) {
			gameTime = finishedTime;
		}

		std::ostringstream timerStr;
		timerStr << gameTime;
		text.setString(timerStr.str());
		renderWindow.draw(text);
	}
	
}

void TimeClimb::Timer::Restart() {
	gameTimeClock.restart();
}

void TimeClimb::Timer::setFinished(bool res)
{
	finished = res;
	finishedTime = gameTimeClock.getElapsedTime().asMilliseconds() / 1000.0;
	text.setCharacterSize(250);
	text.setPosition(500, 200);
}
bool TimeClimb::Timer::getFinished() {
	return finished;
}

void TimeClimb::Timer::reInit() {
	text.setCharacterSize(150);
	gameTimeClock.restart();
	text.setStyle(sf::Text::Bold);
	text.setPosition(50, 400);
	finished = false;
}

float TimeClimb::Timer::getFinishedTime()
{
	return finishedTime;
}
	
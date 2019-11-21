#include "Smash_It_SmashCounter.h"

SmashCounter::SmashCounter():
	text("", font, 150)
{
	text.setStyle(sf::Text::Bold);
	text.setPosition(1750, 100);
	finished = false;
	finishedScore = 0;
	smashCount = 0;
}

SmashCounter::~SmashCounter()
{
}

void SmashCounter::Load(std::string filename) {
	font.loadFromFile(filename);
}

int SmashCounter::getCount() {
	return smashCount;
}

void SmashCounter::Draw(sf::RenderWindow & renderWindow) {

	int score = smashCount;

	if (finished) {
		score = finishedScore;
	}

	std::ostringstream timerStr;
	timerStr << score;
	text.setString(timerStr.str());
	renderWindow.draw(text);
}


void SmashCounter::setFinished(bool res)
{
	finished = res;
	finishedScore = smashCount;
	text.setCharacterSize(250);
	text.setPosition(500, 200);
}
bool SmashCounter::getFinished() {
	return finished;
}

void SmashCounter::reInit() {
	text.setCharacterSize(150);
	smashCount = 0;
	text.setStyle(sf::Text::Bold);
	text.setPosition(1750, 0);
	finished = false;
}

void SmashCounter::countIncroment() {
	smashCount++;
}
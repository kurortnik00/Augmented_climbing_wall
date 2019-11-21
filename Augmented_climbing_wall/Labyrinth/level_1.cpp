#include "level_1.h"

Level_1::Level_1()
	:line1(sf::Vector2f(960, 600), 90, 500),
	startButton(sf::Vector2f(100, 800), 78, "Labyrinth/images/playButton.png", sf::IntRect(0, 0, 156, 156)),
	winButton(sf::Vector2f(800, 200), 50, "Labyrinth/images/winButton.png", sf::IntRect(0, 0, 126, 126))
{
	_isLoaded = false;
	Level_1::Load("Labyrinth/images/2/teslaColor");

}

Level_1::~Level_1()
{

}

void Level_1::Load(std::string filename)
{


	Level::loadTextureArr(filename, 12, line1);
	Level::setSpritesArr(line1, line1.animationTextureArr[0]);
	//line1.spritesArr[0].setScale(2, 1);


	lines.push_back(line1);

	buttons.push_back(startButton);
	buttons.push_back(winButton);

	_isLoaded = true;
}


void Level_1::Draw(sf::RenderWindow & renderWindow)
{

	if (_isLoaded && !VisibleGameObject::getFinished()) {

		Level::drawLines(renderWindow, lines);
		Level::drawButtons(renderWindow, buttons);
	}

	//drow the end of the game 
//last animation and score if win
//the fail map if lose
	else
	{

		Level::win_lose_Draw(renderWindow, lines);

	}




}

void Level_1::Update(sf::Event& event)
{

	Level::lineAnimationUpdate(lines);
	Level::linesUpdate(lines);
	Level::buttonsUpdate(buttons);

}


void Level_1::reInit()
{

}
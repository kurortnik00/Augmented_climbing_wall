#include "Level_2.h"
#include "../mainWindow.h"


Level_2::Level_2()
	:line1(sf::Vector2f(MainWindow::getWindow().getSize().x / 4, MainWindow::getWindow().getSize().y), 330, 1100),
	line2(sf::Vector2f(-25, MainWindow::getWindow().getSize().y / 2), 330, 1100),
	startButton(sf::Vector2f(100, 800), 50, "Labyrinth/images/playButton.png", sf::IntRect(0, 0, 156, 156)),
	winButton(sf::Vector2f(800, 200), 50, "Labyrinth/images/winButton.png", sf::IntRect(0, 0, 126, 126))
	
{
	_isLoaded = false;
	Level_2::Load("Labyrinth/images/2/teslaColor");

}

Level_2::~Level_2()
{

}

void Level_2::Load(std::string filename)
{


	Level::loadTextureArr(filename, 12, line1);
	Level::loadTextureArr(filename, 12, line2);
	Level::setSpritesArr(line1, line1.animationTextureArr[0]);
	Level::setSpritesArr(line2, line2.animationTextureArr[0]);

	lines.push_back(line1);
	lines.push_back(line2);

	buttons.push_back(startButton);
	buttons.push_back(winButton);

	_isLoaded = true;
}


void Level_2::Draw(sf::RenderWindow & renderWindow)
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

void Level_2::Update(sf::Event& event)
{

	Level::lineAnimationUpdate(lines);
	Level::linesUpdate(lines);
	Level::buttonsUpdate(buttons);

}


void Level_2::reInit()
{

}
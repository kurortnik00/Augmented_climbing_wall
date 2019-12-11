#include "level_1.h"

Level_1::Level_1(std::string topScore)
	:line1(Level::config.level1_line1_pos, Level::config.level1_line1_angl, Level::config.level1_line1_length),
	startButton(Level::config.level1_startButton, Level::config.level1_startButton_radius, "Labyrinth/images/playButton.png", sf::IntRect(0, 0, 156, 156)),
	winButton(sf::Vector2f(800, 200), Level::config.level1_winButton_radius, "Labyrinth/images/winButton.png", sf::IntRect(0, 0, 126, 126)),
	Level(topScore)
{
	std::cout << Level::config.level1_line1_pos.x;
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

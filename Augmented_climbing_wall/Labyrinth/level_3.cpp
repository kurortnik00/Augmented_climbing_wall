#include "level_3.h"

Level_3::Level_3(std::string topScore)
	:line1(Level::config.level3_line1_pos, Level::config.level3_line1_angl, Level::config.level3_line1_length),
	line2(Level::config.level3_line2_pos, Level::config.level3_line2_angl, Level::config.level3_line2_length),
	startButton(Level::config.level3_startButton, Level::config.level3_startButton_radius, "Labyrinth/images/playButton.png", sf::IntRect(0, 0, 156, 156)),
	winButton(Level::config.level3_winButton, Level::config.level3_startButton_radius, "Labyrinth/images/winButton.png", sf::IntRect(0, 0, 126, 126)),
	_angVelocity(Level::config.level3_angVel),
	Level(topScore)
{

	
	_isLoaded = false;

	Level_3::Load("Labyrinth/images/2/teslaColor");
	
}

Level_3::~Level_3()
{

}

void Level_3::Load(std::string filename)
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

void Level_3::Draw(sf::RenderWindow & renderWindow)
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

void Level_3::Update(sf::Event& event)
{
	Level::lineAnimationUpdate(lines);
	Level::linesUpdate(lines);
	Level::buttonsUpdate(buttons);

	
	if (!VisibleGameObject::getFinished() && VisibleGameObject::getStart())
	{

		for (int i = 0; i < lines.size(); i++)
		{
			lines[i]._angl += _angVelocity;
		}

	}
}

void Level_3::reInit()
{

}
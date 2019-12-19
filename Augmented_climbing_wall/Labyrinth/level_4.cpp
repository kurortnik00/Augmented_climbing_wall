#include "level_4.h"
#include "../mainWindow.h"

Level_4::Level_4(std::string topScore)
	:blinkLine(Level::config.level4_line1_pos, Level::config.level4_line1_angl, Level::config.level4_line1_length),
	line2(Level::config.level4_line2_pos, Level::config.level4_line2_angl, Level::config.level4_line2_length),
	line3(Level::config.level4_line3_pos, Level::config.level4_line3_angl, Level::config.level4_line3_length),
	line4(Level::config.level4_line4_pos, Level::config.level4_line4_angl, Level::config.level4_line4_length),
	line5(Level::config.level4_line5_pos, Level::config.level4_line5_angl, Level::config.level4_line5_length),
	button1(Level::config.level4_button1, Level::config.level4_button1_radius, "Labyrinth/images/Button.png", sf::IntRect(10,10,115,115)),
	button2(Level::config.level4_button2, Level::config.level4_button2_radius, "Labyrinth/images/Button.png", sf::IntRect(10, 10, 115, 115)),
	startButton(Level::config.level4_startButton, Level::config.level4_startButton_radius, "Labyrinth/images/playButton.png", sf::IntRect(0, 0, 156, 156)),
	winButton(Level::config.level4_winButton, Level::config.level4_winButton_radius, "Labyrinth/images/winButton.png", sf::IntRect(0, 0, 126, 126)),
	Level(topScore)
{

	clockForBlinkLine.restart();


	_isLoaded = false;

	Level_4::Load("Labyrinth/images/2/teslaColor");
	
}

Level_4::~Level_4()
{

}

void Level_4::Load(std::string filename)
{
	Level::loadTextureArr(filename, 12, blinkLine);
	Level::loadTextureArr(filename, 12, line2);
	Level::loadTextureArr(filename, 12, line3);
	Level::loadTextureArr(filename, 12, line4);
	Level::loadTextureArr(filename, 12, line5);

	Level::setSpritesArr(blinkLine, blinkLine.animationTextureArr[0]);
	Level::setSpritesArr(line2, line2.animationTextureArr[0]);
	Level::setSpritesArr(line3, line3.animationTextureArr[0]);
	Level::setSpritesArr(line4, line4.animationTextureArr[0]);
	Level::setSpritesArr(line5, line5.animationTextureArr[0]);

	lines.push_back(blinkLine);;
	lines.push_back(line2);
	lines.push_back(line3);
	lines.push_back(line4);
	lines.push_back(line5);

	buttons.push_back(startButton);
	buttons.push_back(winButton);
	buttons.push_back(button1);
	buttons.push_back(button2);
	
	_isLoaded = true;

}

void Level_4::Draw(sf::RenderWindow & renderWindow)
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
		lines[VERTICAL_LINE_1]._velocity.x = 0;
		lines[VERTICAL_LINE_2]._velocity.x = 0;
		
	}
}

void Level_4::Update(sf::Event& event)
{
	Level::lineAnimationUpdate(lines);
	Level::linesUpdate(lines);
	
	Level::buttonsUpdate(buttons);
	

	if (!VisibleGameObject::getFinished() && VisibleGameObject::getStart())
	{

		for (int i = 0; i < lines.size(); i++)
		{
			blinkLineTime = clockForBlinkLine.getElapsedTime().asMilliseconds();
			if (blinkLineTime > Level::config.level4_timeToSwithOn_blinkLine)
			{
				lines[BLINC_LINE]._unActive = true;

				if (blinkLineTime > Level::config.level4_timeToSwithOff_blinkLine)
				{
					clockForBlinkLine.restart();
					lines[BLINC_LINE]._unActive = false;
				}
			}
			//when touched first action button 
			if (buttons[ACTION_BUTTON_1]._hasClicked)
			{
				lines[BLINC_LINE]._unActive = true;
			}
			if (buttons[ACTION_BUTTON_1]._hasClicked && lines[EXTENTION_LINE_1]._angl > 0)
			{
				//std::cout << Level::config.level4_anglVel << "\n";
				lines[EXTENTION_LINE_1]._angl -= Level::config.level4_anglVel;
				lines[EXTENTION_LINE_2]._angl += Level::config.level4_anglVel;
			}
			//when touched second action button 
			if (buttons[ACTION_BUTTON_2]._hasClicked && lines[VERTICAL_LINE_1]._velocity.x == 0)
			{
				lines[VERTICAL_LINE_1]._velocity.x = -Level::config.level4_vel;
				lines[VERTICAL_LINE_2]._velocity.x = Level::config.level4_vel;

			}
			if (lines[VERTICAL_LINE_1]._startPoint.x <= 0.0 || lines[VERTICAL_LINE_1]._startPoint.x >= 1920.0) lines[VERTICAL_LINE_1]._velocity.x = -lines[VERTICAL_LINE_1]._velocity.x;
			if (lines[VERTICAL_LINE_2]._startPoint.x <= 0.0 || lines[VERTICAL_LINE_2]._startPoint.x >= 1920.0) lines[VERTICAL_LINE_2]._velocity.x = -lines[VERTICAL_LINE_2]._velocity.x;
		}
		
		if (Cliker::getClik(buttons[3]._center - sf::Vector2f(130,0), buttons[3]._radius+50, false))
		{

			if (!buttons[3]._unDrowable)
			{
				buttons[3]._hasClicked = true;
				buttons[3]._unDrowable = true;
			}
		}
		if (Cliker::getClik(buttons[2]._center + sf::Vector2f(0, 40), buttons[2]._radius, false))
		{

			if (!buttons[2]._unDrowable)
			{
				buttons[2]._hasClicked = true;
				buttons[2]._unDrowable = true;
			}
		}
		
	}
}
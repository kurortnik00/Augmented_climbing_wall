#include "level_4.h"
#include "../mainWindow.h"

Level_4::Level_4()
	:blinkLine(sf::Vector2f(-30, MainWindow::getWindow().getSize().y / 3 + 120), 0, 880),
	line2(sf::Vector2f(blinkLine.size.x , 0), 90, 440),
	line3(sf::Vector2f(blinkLine.size.x  + 200, 0), 90, 440),
	line4(sf::Vector2f(blinkLine.size.x + 200, line3._endPoint.y), 90, 210),
	line5(sf::Vector2f(blinkLine.size.x  + 200, MainWindow::getWindow().getSize().y), 270, 210),
	button1(sf::Vector2f(blinkLine.size.x / 2 , 200), 50, "Labyrinth/images/Button.png", sf::IntRect(10,10,115,115)),
	button2(sf::Vector2f(line4._startPoint.x + 300, (line4._startPoint.y + line5._startPoint.y )/2), 50, "Labyrinth/images/Button.png", sf::IntRect(10, 10, 115, 115)),
	startButton(sf::Vector2f(100,800), 50, "Labyrinth/images/playButton.png", sf::IntRect(0, 0, 156, 156)),
	winButton(sf::Vector2f(920,100), 50, "Labyrinth/images/winButton.png", sf::IntRect(0, 0, 126, 126))
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
			if (blinkLineTime > 2500)
			{
				lines[BLINC_LINE]._unActive = true;

				if (blinkLineTime > 3500)
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
				lines[EXTENTION_LINE_1]._angl -= 0.01;
				lines[EXTENTION_LINE_2]._angl += 0.01;
			}
			//when touched second action button 
			if (buttons[ACTION_BUTTON_2]._hasClicked && lines[ACTION_BUTTON_2]._velocity.x == 0)
			{
				lines[VERTICAL_LINE_1]._velocity.x = -0.1;
				lines[VERTICAL_LINE_2]._velocity.x = 0.1;

			}
			if (lines[VERTICAL_LINE_1]._startPoint.x <= 0.0 || lines[VERTICAL_LINE_1]._startPoint.x >= 1920.0) lines[VERTICAL_LINE_1]._velocity.x = -lines[VERTICAL_LINE_1]._velocity.x;
			if (lines[VERTICAL_LINE_2]._startPoint.x <= 0.0 || lines[VERTICAL_LINE_2]._startPoint.x >= 1920.0) lines[VERTICAL_LINE_2]._velocity.x = -lines[VERTICAL_LINE_2]._velocity.x;
		}
	}
}
#pragma once
#include "level.h"
#include "Labyrinth_Game.h"

class Level_4 : public Level
{
public:
	Level_4();
	~Level_4();
	void Draw(sf::RenderWindow & renderWindow);
	void Update(sf::Event& event);
	//void reInit();

private:
	void Load(std::string filename);		//use in Init() function 

	Line blinkLine;
	Line line2;
	Line line3;
	Line line4;
	Line line5;

	Button button1;
	Button button2;
	Button startButton;
	Button winButton;

	std::vector<Line> lines;
	std::vector<Button> buttons;

	sf::Clock clockForBlinkLine;
	float blinkLineTime;

	bool _isLoaded;
	int _trashHold;


	enum lineNames
	{
		BLINC_LINE, VERTICAL_LINE_1, VERTICAL_LINE_2,  EXTENTION_LINE_1, EXTENTION_LINE_2
	};

	enum ButtonNames
	{
		START_BUTTON, WIN_BUTTON, ACTION_BUTTON_1, ACTION_BUTTON_2
	};

};
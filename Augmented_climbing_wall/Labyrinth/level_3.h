#pragma once
#include "level.h"
//#include "Game.h"

class Level_3 : public Level
{
public:
	Level_3(std::string topScore);
	~Level_3();
	void Draw(sf::RenderWindow & renderWindow);
	void Update(sf::Event& event);
	void reInit();

private:
	void Load(std::string filename);		//use in Init() function 
	Line line1;
	Line line2;

	Button startButton;
	Button winButton;

	std::vector<Line> lines;
	std::vector<Button> buttons;

	float _angVelocity;


	bool _isLoaded;


	int _trashHold;

	enum ButtonNames
	{
		START_BUTTON, WIN_BUTTON
	};

};
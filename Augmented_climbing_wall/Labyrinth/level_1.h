#pragma once
#include "level.h"
//#include "Game.h"
//#include "../BodyBasics.h"

class Level_1 : public Level
{
public:
	Level_1(std::string topScore);
	~Level_1();
	void Draw(sf::RenderWindow & renderWindow);
	void Update(sf::Event& event);
private:
	void Load(std::string filename);		//use in Init() function 

	Line line1;
	Button startButton;
	Button winButton;

	std::vector<Line> lines;
	std::vector<Button> buttons;

	bool _isLoaded;
};
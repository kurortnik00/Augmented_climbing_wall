#pragma once

#include "level.h"
#include "Labyrinth_Game.h"

class Level_2 : public Level
{
public:
	Level_2();
	~Level_2();
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


	bool _isLoaded;

};
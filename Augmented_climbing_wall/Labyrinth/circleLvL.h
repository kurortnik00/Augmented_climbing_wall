#pragma once
#include "../stdafx.h"
//#include "../BodyBasics.h"
#include "level.h"
#include <sstream>
#include <cmath>


class CircleLvL : public Level
{
public:
	CircleLvL ();
	~CircleLvL ();
	
	void Draw(sf::RenderWindow & renderWindow);
	void Update(sf::Event& event);
	void reInit();

private:
	sf::Sprite  _sprite;					//sprite of each one animation partical tesla
	bool _isLoaded;							//set in Load()
	void Load(std::string filename);		//use in Init() function 
	sf::CircleShape _shape;					//use for boundering resulutions				
	float _radius;							//inscribed radius of mainCircle 
	sf::Vector2f _position;					//pos of maiCircle left top corner
	sf::Vector2f _velocity;					//velocity of center of rotation 
	float _angl;							//angl of rotation
	sf::Transform transform;				//function that rotate coordinate system
	float _angVelocity;						//rotation velocity
	sf::Clock animationClock;				//animation of moving
	sf::Vector2f _centerOfRotation;			//pos of rotation center
	sf::Vector2f _center;					//pos mainCircles center
	sf::Vector2f _startPos;			//use in Init() and reInit()
	int animationNumber;											//need for count what animation picture is now
	std::vector< sf::Sprite> spritesArr_teslaCircle;				//vector of sprites that used in teslaCircle
	void setSpritesArr_circle(int figureCorners, sf::Texture texture);		//init spritesArr_teslaCircle vector					
	sf::Clock animationClock2;			//clock for animation speed of teslaCircle 
	std::vector<sf::Sprite> spriteArr_line;		////vector of sprites that used in teslaLine 
	float animationTime;		//contains count of miliSeconds from last sprite change (animation)
	int numberTeslaParticals;		//number of particals(small lines) in mainCircle
	float animationTime_dinamic;	////the time of velocity animation, contains  count of miliSeconds from last move (move animation)


	Line line1;
	Button startButton;
	Button winButton;

	std::vector<Line> lines;
	std::vector<Button> buttons;
};


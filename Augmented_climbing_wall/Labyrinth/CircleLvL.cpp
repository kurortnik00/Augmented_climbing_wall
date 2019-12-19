#include "circleLvL.h"
#include "Labyrinth_Game.h"
#include "../mainWindow.h"


#define PI 3.14159265 

CircleLvL::CircleLvL(std::string topScore)
	:_startPos(Level::config.level5_pos),
	_angVelocity(Level::config.level5_anglVel),				//Rotation velocity
	_velocity(Level::config.level5_vel),				//Center velocity, it moves _center
	_radius(Level::config.level5_radius),			//_shape radiuse, it responsible of boundering shape. In fact it equils inscribed radius 
	line1(_center, 0, _radius +40),
	startButton(Level::config.level5_startButton, Level::config.level5_startButton_radius, "Labyrinth/images/playButton.png", sf::IntRect(0, 0, 156, 156)),
	winButton(Level::config.level5_winButton, Level::config.level5_winButton_radius, "Labyrinth/images/winButton.png", sf::IntRect(0, 0, 126, 126)),
	Level(topScore)
{
	_position = sf::Vector2f(_startPos);
	_angl = 0;
	_center = sf::Vector2f(_position.x + _radius, _position.y + _radius);
	_centerOfRotation = sf::Vector2f(_center.x + 300, _center.y);			//dislocated center of rotation. made for shape movement 


	animationClock.restart();		//mabe it not necessaty
	numberTeslaParticals = Level::config.level5_teslaParticls;
	CircleLvL::Load("Labyrinth/images/2/teslaColor");

}

CircleLvL::~CircleLvL() {
	
}

void CircleLvL::Load(std::string filename)
{
	_shape.setRadius(_radius);
	_shape.setPosition(_position);

	Level::loadTextureArr(filename, 12, line1);
	Level::setSpritesArr(line1, line1.animationTextureArr[0]);

	line1._startPoint = _center;
	lines.push_back(line1);

	buttons.push_back(startButton);
	buttons.push_back(winButton);


	setSpritesArr_circle(numberTeslaParticals, line1.animationTextureArr[0]);			//fill the sprites array  'spritesArr_teslaCircle' with the same _texture 
	for (int i = 0; i < spritesArr_teslaCircle.size(); i++) {
		spritesArr_teslaCircle[i].setPosition(_position);			//init the start position of all sprites
	}
	_isLoaded = true;
}

void CircleLvL::Draw(sf::RenderWindow & renderWindow)
{
	//The main phase of game, while not win or lose
	//while has been loaded and not finished it will draw all sprites from 'spriteArr_line' and 'spritesArr_teslaCircle'
	//Buttons and timer draws in relevant classes
	if (_isLoaded && !VisibleGameObject::getFinished())
	{
		for (int i = 0; i < spritesArr_teslaCircle.size(); i++) {
			renderWindow.draw(spritesArr_teslaCircle[i]);		
		}
		Level::drawLines(renderWindow, lines);
		Level::drawButtons(renderWindow, buttons);
	}
	//drow the end of the game 
	//last animation and score if win
	//the fail map if lose
	else
	{

		Level::win_lose_Draw(renderWindow, lines);
		if (Level::getLastAnimation() || !Level::getWin())
		{
			if (!Level::getWin())
			{
				for (int i = 0; i < spritesArr_teslaCircle.size(); i++) {
					renderWindow.draw(spritesArr_teslaCircle[i]);
				}
			}
			

		}
		

	}
}

void CircleLvL::Update(sf::Event& event) {


	Level::lineAnimationUpdate(lines);
	Level::linesUpdate(lines);
	Level::buttonsUpdate(buttons);

	animationTime = animationClock2.getElapsedTime().asMilliseconds();		//time for tesla animation
	if (animationNumber == 12) animationNumber = 0;				//loop the animation
	if (animationTime > 40) {								//the speed of animation
		//int angleCircleTesla = 0;
		for (int i = 0; i < spritesArr_teslaCircle.size(); i++) {
			spritesArr_teslaCircle[i].setTexture(line1.animationTextureArr[animationNumber]);

			double R = _radius*1.2; //Радиус описанной окружности
			double angle = 0; //Угол наклона правильного многоугольника

			for (int j = 0; j < numberTeslaParticals; j++)
			{
				spritesArr_teslaCircle[j].setPosition(sf::Vector2f(_center.x + R * cos(angle*PI / 180) , _center.y + R * sin(angle*PI / 180))); //fill the all next cordinates (sqwears)
				angle = angle + 360 / numberTeslaParticals;				//Увеличиваем угол на величину угла правильного многоугольника
				spritesArr_teslaCircle[j].setRotation(angle+80);			//the rotation of iach tesla partical, if ratation == 0 all particals are parallel  
				
			}	
		}
		
		animationNumber++;		
		animationClock2.restart();
	}
	
	//this part runs when play button presed
	//and runnig until not lost or win (finished)
	if (!VisibleGameObject::getFinished() && VisibleGameObject::getStart())
	{
		
		animationTime_dinamic = animationClock.getElapsedTime().asMilliseconds();			//the time of velocity animation
		//this animation rotates and move the KILL_ring
		if (animationTime_dinamic > 5) {						//the animation speed
			_angl += _angVelocity;

			_center = _center + _velocity;
			if (_center.x + _radius > MainWindow::SCREEN_WIDTH || _center.x - _radius < 0) _velocity = -_velocity;
				//coordinateTransf(_angVelocity, _center, _centerOfRotation);		//canculation of new position of _center (the center of KILL_ring)

			//rotation of kill line 
			//not visible, only for canculations of itaractions
			for (int j = 0; j < lines.size(); j++) {
				lines[j]._startPoint = _center;
				lines[j]._angl = _angl;
			}
			animationClock.restart();
		}
		if (_angl > 360) _angl -= 360;



		//canculate and Update the iteraction with the plaer
		//responsible of losing state
		//win check in "winButton"
		if (!VisibleGameObject::getKinectControll()) {
			if ((dist2(sf::Vector2f(sf::Mouse::getPosition(MainWindow::getWindow()).x, sf::Mouse::getPosition(MainWindow::getWindow()).y), _center) > _radius*_radius))
			{
				Level::lose(sf::Vector2f(sf::Mouse::getPosition(MainWindow::getWindow()).x, sf::Mouse::getPosition(MainWindow::getWindow()).y));
			}
			
		}
		
	}

}


void CircleLvL::reInit() {

}


void CircleLvL::setSpritesArr_circle(int figureCorners, sf::Texture texture)
{
	for (int i = 0; i < figureCorners; i++) {
		_sprite.setTexture(texture);
		spritesArr_teslaCircle.push_back(_sprite);
	}
}

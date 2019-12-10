#pragma once
#include "../stdafx.h"
//#include "../BodyBasics.h"
//#include "Labyrinth_Game.h"
#include "Labyrinth_VisibleGameObject.h"
#include "../Cliker.h"
#include "../mainWindow.h"
#include <sstream>
#include <cmath>
#include "Labyrinth_config.h"
#include "Labyrinth_Timer.h"
#include "../myKeyboard.h"
#include <random>
#include <iomanip>
#include "../server.h"

#define PI 3.14159265 

class Level : public Labyrinth::VisibleGameObject
{
public:
	Level();
	~Level();
	void win(sf::Vector2f pos);
	void lose(sf::Vector2f pos);
	
	sf::CircleShape getWinShape();
	sf::CircleShape getLoseShape();
	float dist2(sf::Vector2f const & p1, sf::Vector2f const & p2);			//sqwere of dist betwin two points
	static sf::Vector2f coordinateTransf(float angl, sf::Vector2f & oldPoint, sf::Vector2f & centerOfRotation);		//returns new point after rotation around the point
	float lineEquation(sf::Vector2f & point1, sf::Vector2f & point2, sf::Vector2f const & mouse);		//function use for canculate collisions with line
	void setGameResult(std::string gameResult);			//set "win" or "lose" title
	std::string getGameResult();
	void setLastAnimation(bool lastAnimation);			//set flag that last animation hss fineshed
	bool getLastAnimation();
	bool getWin();
	void winRadiusIncr();
	void setWin(bool win);
	void showTopScore();
	void TOP_List_Update();
	void TOP_List_Draw();

	static Labyrinth::Config config;
	

//protected:
	struct Line
	{
	public:
		Line(sf::Vector2f startPoint, float angl, float length);
		sf::RectangleShape _shape;
		sf::Vector2f size;
		sf::Vector2f _startPoint;
		sf::Vector2f _endPoint;
		float _angl;
		//int _numberTeslaParticals;
		float _length;
		std::vector< sf::Texture> animationTextureArr;			//vector of tetures that used in teslaCircle
		//std::vector< sf::Sprite> spritesArr;				//vector of sprites that used in teslaCircle
		sf::Sprite sprite;
		sf::Vector2f _center;
		sf::Vector2f _velocity;
		bool _unActive;
		//EndLine circle 
		float circleRadius;
		sf::CircleShape circleShape1;
		sf::CircleShape circleShape2;
		
		
	};

	struct Button
	{
	public:
		Button(sf::Vector2f position, float radius, std::string filename, sf::IntRect textureRect);
		sf::Vector2f _position;
		float _radius;
		bool _hasClicked;
		bool _unDrowable;
		sf::Sprite  _sprite;
		sf::Texture _texture;
		sf::Image _image;
		std::string _filename;
		
		sf::Vector2f _center;

	};

	void loadTextureArr(std::string filename, int animationCount, Line& line);		//load textures and init animationTextureArr_tesla vector
	void setSpritesArr(Line& line, sf::Texture texture);		//init spritesArr_teslaCircle vector
	//void setLineCorrection(Line& line, sf::Vector2f correction);
	void linesUpdate(std::vector<Line>& lines);
	void lineAnimationUpdate(std::vector<Line>& lines);
	void win_lose_Draw(sf::RenderWindow & renderWindow, std::vector<Line>& lines);
	void drawLines(sf::RenderWindow & renderWindow, std::vector<Line>& lines);
	void drawButtons(sf::RenderWindow & renderWindow, std::vector<Button>& lines);
	void buttonsUpdate(std::vector<Button>& Buttons);

	
	

private:
	//void init();
	bool _win;
	sf::CircleShape _winShape;				//shape of win animation
	float _winShapeRadius;
	sf::CircleShape _loseShape;				//shape that shows wher euou faild
	float _loseShapeRadius;
	std::string _gameResult;	 //contains "win" or "lose" title
	bool _lastAniamation;				//flag is lastAnimation has been finished
	sf::Font _font;		//for timer and "win" or "lose" title
	sf::Text _text;		//for timer and "win" or "lose" title
	sf::Clock animationClock;
	float animationTime;
	int animationNumber;
	float _trashHold;
	std::set<std::pair<float, std::string>> TOP_List;
	//Labyrinth::Timer endGameTimer;
	sf::Clock clock;
	sf::Clock serverDelayClock;
	bool win_lose_Draw_first;
	
	bool TOPScore_updated;
	Button restartButton;

	sf::Music music;//создаем объект музыки

	sf::SoundBuffer win_soundBuffer;
	sf::Sound winSound;
	sf::SoundBuffer lose_soundBuffer;
	sf::Sound loseSound;
	sf::SoundBuffer button_soundBuffer;
	sf::Sound buttonSound;

	//float kinectTranform_X_Cordinates(float x);
	//float kinectTranform_Y_Cordinates(float y);


	//bool _finished;

	enum defoltButtonNames
	{
		START_BUTTON, WIN_BUTTON
	};


	enum jointTypes{
		SPINEBASE,
		SPINEMID,
		NECK,
		HEAD,
		SHOULDERLEFT,
		ELBOWLEFT,
		WRISTLEFT,
		HANDLEFT,
		SHOULDERRIGHT,
		ELBOWRIGHT,
		WRISTRIGHT,
		HANDRIGHT,
		HIPLEFT,
		KNEELEFT,
		ANKLELEFT,
		FOOTLEFT,
		HIPRIGHT,
		KNEERIGHT,
		ANKLERIGHT,
		FOOTRIGHT,
		SPINESHOULDER,
		HANDTIPLEFT,
		THUMBLEFT,
		HANDTIPRIGHT,
		THUMBRIGHT,
	};


	float additionalRadius(int joint);

	static std::string name;

};
#include "Smash_It_MainMenu.h"
#include "../Cliker.h"
//#include "../body_tracker.h"

Smash_It::MainMenu::MenuItem::MenuItem(sf::Vector2f position, MenuResult action)
	:_position(position), text("", font, 110), _action(action)
{
	font.loadFromFile("Smash_It/font/18123.ttf");
	text.setFillColor(sf::Color(0, 0, 0));
	sf::Image image;
	image.loadFromFile("Smash_It/images/menu/1.png");
	image.createMaskFromColor(sf::Color(255, 255, 255));
	_texture.loadFromImage(image);
	_sprite.setTexture(_texture);
	_sprite.setPosition(_position);
	_sprite.setColor(sf::Color(255, 255, 255, 100));	
	animationFrame = 0;
	_radius = 150;
	
	_center = sf::Vector2f(position.x + _sprite.getTexture()->getSize().x / 2, position.y + _sprite.getTexture()->getSize().y / 2);


	image.loadFromFile("Smash_It/images/menu/string-1.png");
	image.createMaskFromColor(sf::Color(255, 255, 255));
	_stringTexture.loadFromImage(image);
	_stringSprite.setTexture(_stringTexture);
	_stringSprite.setPosition(_center + sf::Vector2f(-30, 150));
	_stringSprite.setColor(sf::Color(255, 255, 255, 100));
}

Smash_It::MainMenu::MenuResult Smash_It::MainMenu::Show(sf::RenderWindow& window, std::set<std::pair<float, std::string>>& TOP_List, myServer &server)
{
	MainMenu::velocity = sf::Vector2f(0, 0.02);
	//Load menu image from file
	sf::Image image;
	image.loadFromFile("Smash_It/images/back_ground_1.png");
	sf::Texture texture;//создаем объект Texture (текстура)
	texture.loadFromImage(image);//передаем в него объект Image (изображения)
	//создаем объект Sprite(спрайт)
	sprite.setTexture(texture);//передаём в него объект Texture (текстуры)
	sprite.setColor(sf::Color(255, 255, 255, 100));




	//Play menu item coordinates
	MenuItem playButton(sf::Vector2f(700,100), Play);
	std::ostringstream play_buttonStr;
	playButton.text.setCharacterSize(85);
	playButton.text.setString(L"Играть");
	playButton.text.setPosition(playButton._center - sf::Vector2f(130, 80));
	playButton.text.setFillColor(sf::Color(255, 255, 255, 100));


	_menuItems.push_back(playButton);

	Draw(window);
	
	MenuResult clicResult = GetMenuResponse(window, server);
	
	if (clicResult == Score_board)
	{
		int scoresCount = 1;
		std::vector<sf::Text> plaersScore;
		sf::Font font;
		font.loadFromFile("Smash_It/font/11583.ttf");



		std::set<std::pair<float, std::string>>::reverse_iterator rit;

		for (rit = TOP_List.rbegin(); rit != TOP_List.rend(); ++rit)
		{

			std::string plaerScore_str = std::to_string(scoresCount) + ". " + rit->second + "       " + std::to_string((int)rit->first);
			sf::Text plaerScore(plaerScore_str, font, 150);
			plaerScore.setPosition(window.getSize().x / 2 - 400, 200 + 100 * scoresCount);
			plaersScore.push_back(plaerScore);

			scoresCount++;
		}

		//Top score screen
		bool flag = true;
		while (flag)
		{
			sf::Text topScore("TOP SCORE", font, 150);
			topScore.setPosition(window.getSize().x / 2 - 400, 100);


			window.clear(sf::Color(0, 0, 0));
			window.draw(topScore);
			for (int i = 0; i < plaersScore.size(); i++)
			{
				window.draw(plaersScore[i]);
			}
			
			window.display();

			//delay for no frizing 
			if (serverDelayClock.getElapsedTime().asMilliseconds() > 500) {
				std::vector<int> data = server.getData();
				//2 - byte contains information about presed buttons (magick number from client)
				// +=5 need becose with time delation we stack more then one message, and information about prest button will be only in one message
				for (int i = 2; i < data.size(); i += 5)
				{
					if (data[i] == 4) flag = false;
					serverDelayClock.restart();
				}
			}

		}

		
	}

	return clicResult;
}



void Smash_It::MainMenu::Draw(sf::RenderWindow& window)
{
	window.clear(sf::Color(0, 0, 0)); 
	window.draw(sprite);
	std::list<MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		window.draw((*it)._stringSprite);
		window.draw((*it)._sprite);
		window.draw((*it).text);
	}


	sf::CircleShape _shape1;
	float _radius = 30;
	_shape1.setFillColor(sf::Color(0, 0, 0));
	_shape1.setRadius(_radius);
	_shape1.setOutlineThickness(10);
	_shape1.setOutlineColor(sf::Color(250, 50, 100));
	float x = Cliker::kinectTranform_X_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(Limbs::Type::RIGHT_HAND, true).x);
	float y = Cliker::kinectTranform_Y_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(Limbs::Type::RIGHT_HAND, true).y);
	_shape1.setPosition(sf::Vector2f(x, y));

	sf::CircleShape _shape2;
	_shape2.setFillColor(sf::Color(0, 0, 0));
	_shape2.setRadius(_radius);
	_shape2.setOutlineThickness(10);
	_shape2.setOutlineColor(sf::Color(250, 150, 100));
	x = Cliker::kinectTranform_X_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(Limbs::Type::LEFT_HAND, true).x);
	y = Cliker::kinectTranform_Y_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(Limbs::Type::LEFT_HAND, true).y);
	_shape2.setPosition(sf::Vector2f(x, y));


	window.draw(_shape1);
	window.draw(_shape2);

	window.display();
}

void Smash_It::MainMenu::Update(sf::RenderWindow& window)
{
	std::list<MenuItem>::iterator it;
	
	

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		(*it).Move(velocity);
		
	}
	k++;
	if (k > 5000)
	{
		velocity = -velocity;
		k = 0;
	}
}



Smash_It::MainMenu::MenuResult Smash_It::MainMenu::HandleClick(sf::RenderWindow& window, int x, int y)				//Проверка куда кликнули мышью
{
	std::list<MenuItem>::iterator it;
	
	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		float radius = (*it)._radius;
		if (dist2((*it)._center, sf::Vector2f(x,y)) < radius*radius)
		{
			return (*it)._action;										//Возврацает номер "сцены" (состояния)
		}
	}

	return Nothing;
}

Smash_It::MainMenu::MenuResult  Smash_It::MainMenu::GetMenuResponse(sf::RenderWindow& window, myServer &server)
{
	sf::Event menuEvent;
	

	while (true)
	{
		MainMenu::Update(window);
		MainMenu::Draw(window);

		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed)
			{
				return HandleClick(window, menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}
			if (menuEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
		//delay for no frizing 
		if (serverDelayClock.getElapsedTime().asMilliseconds() > 500) {
			std::vector<int> data = server.getData();
			//2 - byte contains information about presed buttons (magick number from client)
			// +=5 need becose with time delation we stack more then one message, and information about prest button will be only in one message
			for (int i = 2; i < data.size(); i += 5)
			{
				if (data[i] == 4) return Exit;  //4 - BACK button presed (magick number from client)
				if (data[i] == 5) return Score_board;
				
				if (data[i] == 1) //PLAY button presed (make full brightness)
				{
					std::list<MenuItem>::iterator it;
					for (it = _menuItems.begin(); it != _menuItems.end(); it++)
					{
						it->_sprite.setColor(sf::Color(255, 255, 255, 255));
						it->_stringSprite.setColor(sf::Color(255, 255, 255, 255));
						it->text.setFillColor(sf::Color(255, 255, 255, 255));
					}
					sprite.setColor(sf::Color(255, 255, 255, 255));
				}
				serverDelayClock.restart();
			}
		}
		//it works while we have start button first in _menuItems
		if (Cliker::getClik(_menuItems.begin()->_center, _menuItems.begin()->_radius, true)) //event here are useles, THIS function do not atact with mouse clikes
		{
			return Play;
		}
	}
}

float Smash_It::MainMenu::dist2(sf::Vector2f const & p1, sf::Vector2f const & p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

void Smash_It::MainMenu::MenuItem::Move(sf::Vector2f pos)
{
	_sprite.move(pos);
	_stringSprite.move(pos);
	text.move(pos);
}
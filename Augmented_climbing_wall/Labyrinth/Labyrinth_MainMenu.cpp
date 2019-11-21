
#include "Labyrinth_MainMenu.h"


Labyrinth::MainMenu::MenuResult Labyrinth::MainMenu::Show(sf::RenderWindow& window)
{

	int w = 110;
	int h = 110;
	sf::Image image;
	sf::Texture texture;
	sf::Vector2i  play(0,180);
	sf::Vector2f  highScore(177,3057);
	sf::Vector2f  back(0,2875);
	sf::Vector2f  next(0,3055);
	sf::Vector2f  exit(177,360);


	sf::Sprite sprite;
	image.loadFromFile("Labyrinth/images/icon-active.png");
	image.createMaskFromColor(sf::Color(237,28,36));
	texture.loadFromImage(image);


	sf::Sprite sprite_play;
	sprite_play.setTexture(texture);
	sprite_play.setTextureRect(sf::IntRect(play.x, play.y, w, h));
	sprite_play.setPosition(800, 300);
	//Setup clickable regions
	//Play menu item coordinates
	MenuItem playButton;
	playButton.rect = sprite_play.getTextureRect();
	playButton.rect.left = sprite_play.getPosition().x;		//becouse "getTextureRect" returns rect from "setTextureRect"
	playButton.rect.top = sprite_play.getPosition().y;
	playButton.action = Play;


	sf::Sprite sprite_exit;
	sprite_exit.setTexture(texture);
	sprite_exit.setTextureRect(sf::IntRect(exit.x, exit.y, w, h));
	sprite_exit.setPosition(1750, 100);
	MenuItem exitButton;
	exitButton.rect = sprite_exit.getTextureRect();
	exitButton.rect.left = sprite_exit.getPosition().x;		
	exitButton.rect.top = sprite_exit.getPosition().y;
	exitButton.action = Exit;


	sf::Sprite sprite_highScore;
	sprite_highScore.setTexture(texture);
	sprite_highScore.setTextureRect(sf::IntRect(highScore.x, highScore.y, w, h));
	sprite_highScore.setPosition(1010, 300);
	MenuItem highScoreButton;
	highScoreButton.rect = sprite_highScore.getTextureRect();
	highScoreButton.rect.left = sprite_highScore.getPosition().x;	
	highScoreButton.rect.top = sprite_highScore.getPosition().y;
	highScoreButton.action =  Nothing;


	sf::Sprite sprite_back;
	sprite_back.setTexture(texture);
	sprite_back.setTextureRect(sf::IntRect(back.x, back.y, w, h));
	sprite_back.setPosition(590, 300);
	MenuItem backButton;
	backButton.rect = sprite_back.getTextureRect();
	backButton.rect.left = sprite_back.getPosition().x;
	backButton.rect.top = sprite_back.getPosition().y;
	backButton.action = PreviousLevel;

	sf::Sprite sprite_next;
	sprite_next.setTexture(texture);
	sprite_next.setTextureRect(sf::IntRect(next.x, next.y, w, h));
	sprite_next.setPosition(1220, 300);
	MenuItem nextButton;
	nextButton.rect = sprite_next.getTextureRect();
	nextButton.rect.left = sprite_next.getPosition().x;
	nextButton.rect.top = sprite_next.getPosition().y;
	nextButton.action = NextLevel;



	sf::Image image_background;
	image_background.loadFromFile("Labyrinth/images/menu_background.png");
	sf::Texture texture_background;//создаем объект Texture (текстура)
	texture_background.loadFromImage(image_background);//передаем в него объект Image (изображения)
	sf::Sprite sprite_background;//создаем объект Sprite(спрайт)
	sprite_background.setTexture(texture_background);//передаём в него объект Texture (текстуры)
	sprite_background.setColor(sf::Color(255, 255, 255, 50));


	
	

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);
	_menuItems.push_back(highScoreButton);
	_menuItems.push_back(backButton);
	_menuItems.push_back(nextButton);


	window.clear(sf::Color(0, 0, 0));
	window.draw(sprite_background);
	window.draw(sprite_exit);
	window.draw(sprite_play);
	window.draw(sprite_highScore);
	window.draw(sprite_back);
	window.draw(sprite_next);
	
	
	
	window.display();


	return GetMenuResponse(window);
}

Labyrinth::MainMenu::MenuResult Labyrinth::MainMenu::HandleClick(int x, int y)				//Проверка куда кликнули мышью
{
	std::list<MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if (menuItemRect.height + menuItemRect.top > y
			&& menuItemRect.top < y
			&& menuItemRect.left < x
			&& menuItemRect.width + menuItemRect.left> x)
		{
			return (*it).action;										//Возврацает номер "сцены" (состояния)

		}
	}

	return Nothing;
}

Labyrinth::MainMenu::MenuResult  Labyrinth::MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while (true)
	{

		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed)
			{
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}
			if (menuEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
	}
}
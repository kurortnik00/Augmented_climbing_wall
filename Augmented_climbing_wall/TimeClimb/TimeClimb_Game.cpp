#include "TimeClimb_Game.h"


TimeClimb::Game::Game(sf::RenderWindow &window)
	:_mainWindow(window)
{
	TimeClimb::Game::_gameState = Uninitialized;
	TimeClimb::Game::targetCount = 3;
	TimeClimb::Game::TOP_List = { {6, "ASd"} , {5, "zzz"} , {1, "qq"} , {4, "44"} };
	TimeClimb::Game::kinectControl = false;
	TimeClimb::Game::_font = "TimeClimb/font/11583.ttf";
}

void TimeClimb::Game::Start(myServer &server)	//инициализация объектов
{
	if (_gameState != Uninitialized) return;

	Game::Init(targetCount);


	_gameState = Game::ShowingMenu;	

	while (!IsExiting())
	{
		GameLoop(server);
		//delay for no frizing 
		std::vector<int> data = getClientData(server);
		for (int i = 2; i < data.size(); i += 5)
		{
			if (data[i] == 4) _gameState = Game::Exiting;  //4 - BACK button presed (magick number from client)			
		}
	}

	_gameState = Uninitialized;
	_gameObjectManager.RemoveAll();
}

bool TimeClimb::Game::IsExiting()//для остановки GameLoop()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

sf::RenderWindow& TimeClimb::Game::GetWindow()
{
	return Game::_mainWindow;
}

void TimeClimb::Game::GameLoop(myServer &server)
{
	sf::Event currentEvent;
	//_mainWindow.pollEvent(currentEvent);
	
	switch (_gameState)
	{
		
		case Game::ShowingMenu:
		{
			ShowMenu(server);
			break;
		}
		/*case Game::ShowingSplash:
		{
		
			ShowSplashScreen();
			break;
		}*/
		case Game::Custom:
		{

			ShowCustomScreen();
			break;
		}
		case Game::Playing:
		{
		
			
			_mainWindow.clear(sf::Color(0, 0, 0));
			
			_gameObjectManager.setAllPlased();
			
			_gameObjectManager.UpdateAll(currentEvent);		//Обновляет все объекты
			_gameObjectManager.DrawAll(_mainWindow);		//Рисует все объекты


			if ((_gameObjectManager.Get(std::to_string(targetCount - 1))->getClickState()) && !(_gameObjectManager.Get("timer1")->getFinished())) {
				_gameObjectManager.Get("timer1")->setFinished(true);
				for (int i = 0; i < targetCount; i++) {
					_gameObjectManager.Get(std::to_string(i))->setFinished(true);
				}

				_gameState = Game::GameOver;
			}

			_mainWindow.display();

			if (currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;

			if (currentEvent.type == sf::Event::KeyPressed)
			{
				if (currentEvent.key.code == sf::Keyboard::Escape)		//Выход из сцены игры в меню по клавише ESC
				{
					//_gameObjectManager.RemoveAll();
					_gameState = Game::ShowingMenu;
				}
			}
			break;
		}
		case Game::GameOver:
		{
			GameOver_Screen(server);
		}
	}
}

//void Game::ShowSplashScreen()
//{
//	SplashScreen splashScreen;
//	splashScreen.Show(_mainWindow);					//Внутри бесконечный цикл прерываемый по нажатию любой клавиши
//													
//	_gameState = Game::ShowingMenu;
//}

void TimeClimb::Game::ShowCustomScreen()
{
	CustomScreen customScreen;
	customScreen.Show(_mainWindow, _gameObjectManager);					//Внутри бесконечный цикл прерываемый по нажатию любой клавиши

	_gameState = Game::ShowingMenu;
}

void TimeClimb::Game::ShowMenu(myServer& server)
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow, TOP_List, server);   //Возврацает значение нажатой "кнопки", т.е. что делать дальше: Играть или выйти из игры
																//Внутри бесконечный цикл прерываемый по нажатию одной из "кнопок" или закрытию окна
																	

	switch (result)
	{
		case MainMenu::Exit:
			_gameState = Game::Exiting;
			break;
		case MainMenu::Play:
			_gameState = Game::Playing;
			Game::reInit(targetCount);
			break;
		case MainMenu::Custom:
			_gameState = Game::Custom;
			Game::reInit(targetCount);
	}
}

void TimeClimb::Game::Init(int targ_count) {

	for (int i = 0; i < targ_count; i++) {
		Target *tar = new Target();
		tar->Load("TimeClimb/images/target2.png");
		tar->SetPosition(200 + 200*i, 500);
		//tar->setKinectControl(kinectControl);
		_gameObjectManager.Add(std::to_string(i), tar);
	}

	Timer *time1 = new Timer();
	time1->Load("TimeClimb/font/11583.ttf");
	_gameObjectManager.Add("timer1", time1);
}

void TimeClimb::Game::reInit(int targ_count)
{
	for (int i = 0; i < targ_count; i++) {
		_gameObjectManager.Get(std::to_string(i))->reInit();
	}
	_gameObjectManager.Get("timer1")->reInit();
}


void TimeClimb::Game::TOP_List_Update(myServer& server)
{
	sf::Event currentEvent;
	std::string name = "";
	std::string scoreString = "Score: ";

	std::stringstream stream;
	stream << std::fixed << std::setprecision(3) << _gameObjectManager.Get("timer1")->getFinishedTime();
	scoreString += stream.str();


	clock.restart();
	bool flag = true;
	while (flag)
	{
		_mainWindow.pollEvent(currentEvent);
		if (currentEvent.type == sf::Event::KeyPressed)
		{
			name += MyKeyboard::getChar();
		}

		_mainWindow.clear(sf::Color(0, 0, 0));

		sf::Font font;
		font.loadFromFile(_font);

		sf::Text gameOverText("Game Over", font, 150);
		gameOverText.setPosition(_mainWindow.getSize().x / 2 - 600, 100);

		sf::Text scoreText(scoreString, font, 150);
		scoreText.setPosition(_mainWindow.getSize().x / 2 - 600, 250);

		sf::Text text(name, font, 150);
		text.setPosition(_mainWindow.getSize().x / 2 - 500, 400);


		_mainWindow.draw(text);
		_mainWindow.draw(scoreText);
		_mainWindow.draw(gameOverText);
		std::vector<int> data = getClientData(server);
		for (int i = 2; i < data.size(); i += 5)
		{
			if (data[i] == 4) flag = false;  //4 - BACK button presed (magick number from client)			
		}


		if (clock.getElapsedTime().asSeconds() > 3)
		{
			sf::Image image;
			image.loadFromFile("Smash_It/images/restart.png");
			sf::Texture texture;
			texture.loadFromImage(image);
			sf::Sprite sprite;
			sprite.setTexture(texture);
			sprite.setScale(0.4, 0.4);
			sf::Vector2f pos(1200, 200);
			sprite.setPosition(pos);
			sf::Vector2f center(pos.x + texture.getSize().x / 4, pos.y + texture.getSize().y / 4);


			if (Cliker::getClik(center, texture.getSize().x / 4, true, myServer::TIME_CLIMB, Modes::Type::SingleBody))
			{
				flag = false;
			}

			_mainWindow.draw(sprite);
		}

		_mainWindow.display();
	}

	if (TOP_List.size() > 4) TOP_List.erase(TOP_List.begin());

	TOP_List.insert(std::make_pair(_gameObjectManager.Get("timer1")->getFinishedTime(), name));



}

std::vector<int> TimeClimb::Game::getClientData(myServer& server)
{
	//delay for no frizing 
	if (serverDelayClock.getElapsedTime().asMilliseconds() > 500) {
		std::vector<int> data = server.getData();
		//2 - byte contains information about presed buttons (magick number from client)
		// +=5 need becose with time delation we stack more then one message, and information about prest button will be only in one message
		serverDelayClock.restart();
		return data;
	}
}



void TimeClimb::Game::GameOver_Screen(myServer& server)
{
	TOP_List_Update(server);
	_gameState = Game::ShowingMenu;
}




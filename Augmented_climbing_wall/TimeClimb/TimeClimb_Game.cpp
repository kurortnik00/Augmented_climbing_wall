#include "TimeClimb_Game.h"


void TimeClimb::Game::Start(myServer &server)	//инициализация объектов
{
	if (_gameState != Uninitialized) return;

	_mainWindow.create(sf::VideoMode(1200, 800), "Pang!");

	Game::Init(targetCount);


	_gameState = Game::Custom;		//Начинаем с заставки

	while (!IsExiting())
	{
		GameLoop(server);
		//delay for no frizing 
		if (serverDelayClock.getElapsedTime().asMilliseconds() > 500) {
			std::vector<int> data = server.getData();
			//2 - byte contains information about presed buttons (magick number from client)
			// +=5 need becose with time delation we stack more then one message, and information about prest button will be only in one message
			for (int i = 2; i < data.size(); i += 5)
			{
				if (data[i] == 4) _gameState = Game::Exiting;  //4 - BACK button presed (magick number from client)
				serverDelayClock.restart();
			}

		}

	}

	_mainWindow.close();
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
	_mainWindow.pollEvent(currentEvent);
	
	switch (_gameState)
	{
		
		case Game::ShowingMenu:
		{
			ShowMenu();		
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
			GameOver_Screen();
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

void TimeClimb::Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow, TOP_List);   //Возврацает значение нажатой "кнопки", т.е. что делать дальше: Играть или выйти из игры
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
	}
}

void TimeClimb::Game::Init(int targ_count) {

	for (int i = 0; i < targ_count; i++) {
		Target *tar = new Target();
		tar->Load("TimeClimb/images/target2.png");
		tar->SetPosition(200 + 200*i, 500);
		tar->setKinectControl(kinectControl);
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


void TimeClimb::Game::TOP_List_Update()
{
	sf::Event currentEvent;
	std::string name = "";
	std::string scoreString = "Score: ";

	std::stringstream stream;
	stream << std::fixed << std::setprecision(3) << _gameObjectManager.Get("timer1")->getFinishedTime();
	scoreString += stream.str();


	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		_mainWindow.pollEvent(currentEvent);
		if (currentEvent.type == sf::Event::KeyPressed)
		{
			name += MyKeyboard::getChar();
		}

		_mainWindow.clear(sf::Color(0, 0, 0));

		sf::Font font;
		font.loadFromFile("TimeClimb/font/11583.ttf");

		sf::Text gameOverText("Game Over", font, 150);
		gameOverText.setPosition(_mainWindow.getSize().x / 2 - 400, 100);

		sf::Text scoreText(scoreString, font, 150);
		scoreText.setPosition(_mainWindow.getSize().x / 2 - 400, 250);

		sf::Text text(name, font, 150);
		text.setPosition(_mainWindow.getSize().x / 2 - 300, 400);


		_mainWindow.draw(text);
		_mainWindow.draw(scoreText);
		_mainWindow.draw(gameOverText);
		_mainWindow.display();
	}


	if (TOP_List.size() > 4) TOP_List.erase(TOP_List.begin());

	TOP_List.insert(std::make_pair(_gameObjectManager.Get("timer1")->getFinishedTime(), name));



}



void TimeClimb::Game::GameOver_Screen()
{
	TOP_List_Update();
	_gameState = Game::ShowingMenu;
}

TimeClimb::GameObjectManager TimeClimb::Game::_gameObjectManager;
TimeClimb::Game::GameState TimeClimb::Game::_gameState = Uninitialized;
sf::RenderWindow TimeClimb::Game::_mainWindow;
int TimeClimb::Game::targetCount = 3;
std::set<std::pair<float, std::string>> TimeClimb::Game::TOP_List = { {6, "ASd"} , {5, "zzz"} , {1, "qq"} , {4, "44"} };
bool TimeClimb::Game::kinectControl = false;
sf::Clock TimeClimb::Game::serverDelayClock;



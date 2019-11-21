#include "Smash_It_Game.h"

 
void Smash_It::Game::Start(myServer &server)	//инициализация объектов
{
	if (_gameState != Uninitialized) return;

	_mainWindow.create(sf::VideoMode(1900, 1080), "Pang!");

	Game::Init(targetCount);
	srand(static_cast<unsigned int>(time(0)));


	_gameState = Game::ShowingMenu;		//Начинаем с меню

	while (!IsExiting())
	{
		GameLoop(server);
		//delay for no frizing 
		if (serverDelayClock.getElapsedTime().asMilliseconds() > 500) {
			std::vector<int> data =  server.getData();
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

bool Smash_It::Game::IsExiting()//для остановки GameLoop()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

sf::RenderWindow& Smash_It::Game::GetWindow()
{
	return Game::_mainWindow;
}

void Smash_It::Game::GameLoop(myServer &server)
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	
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
		case Game::Playing:
		{
		
			
			_mainWindow.clear(sf::Color(0, 0, 0));
			
			_gameObjectManager.setAllPlased();
			
			_gameObjectManager.UpdateAll(currentEvent);		//Обновляет все объекты
			_gameObjectManager.DrawAll(_mainWindow);		//Рисует все объекты

			_mainWindow.display();

			if (currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;

			if (currentEvent.type == sf::Event::KeyPressed)
			{
				if (currentEvent.key.code == sf::Keyboard::Escape)		//Выход из сцены игры в меню по клавише ESC
				{
					_gameState = Game::ShowingMenu;
				}
			}
			if (_gameObjectManager.Get("timer1")->getFinished())
			{
				_gameState = Game::GameOver;
				
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


void Smash_It::Game::ShowMenu(myServer &server)
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
	}
}

void Smash_It::Game::Init(int targ_count) {
	std::string targetFileNames[7] = {							//max targets = 14
		"Smash_It/images/balloon_green.png", "Smash_It/images/balloon_blue.png", "Smash_It/images/balloon_orange.png", "Smash_It/images/balloon_pinck.png",
		"Smash_It/images/balloon_purple.png", "Smash_It/images/balloon_red.png", "Smash_It/images/balloon_yellow.png"
	};
	

	for (int i = 0; i < targ_count; i++) {
		Target *tar = new Target();
		tar->Load(targetFileNames[i]);
		tar->setKinectControl(kinectControl);
		_gameObjectManager.Add(std::to_string(i), tar);
	}

	Timer *time1 = new Timer();
	time1->Load("Smash_It/font/11583.ttf");
	_gameObjectManager.Add("timer1", time1);

	SmashCounter *counter = new SmashCounter();
	counter->Load("Smash_It/font/11583.ttf");
	_gameObjectManager.Add("counter", counter);


	
}

void Smash_It::Game::reInit(int targ_count)
{
	for (int i = 0; i < targ_count; i++) {
		_gameObjectManager.Get(std::to_string(i))->reInit();
	}
	_gameObjectManager.Get("timer1")->reInit();
	_gameObjectManager.Get("counter")->reInit();
}


void Smash_It::Game::countIncriment() {

}

int Smash_It::Game::getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// Равномерно распределяем рандомное число в нашем диапазоне
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void Smash_It::Game::TOP_List_Update()
{

	sf::Event currentEvent;	
	std::string name = "";
	std::string scoreString = "Score: ";

	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << (int) _gameObjectManager.Get("counter")->getCount();
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
		font.loadFromFile("Smash_It/font/11583.ttf");

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

	TOP_List.insert(std::make_pair(_gameObjectManager.Get("counter")->getCount(), name));
	
	

}



void Smash_It::Game::GameOver_Screen()
{
	TOP_List_Update();
	_gameState = Game::ShowingMenu;
}

Smash_It::GameObjectManager Smash_It::Game::_gameObjectManager;
Smash_It::Game::GameState Smash_It::Game::_gameState = Uninitialized;
sf::RenderWindow Smash_It::Game::_mainWindow;
int Smash_It::Game::targetCount = 7;				//max targets = 14 if you wana more change Init()
std::set<std::pair<float, std::string>> Smash_It::Game::TOP_List = { {6, "ASd"} , {5, "zzz"} , {1, "qq"} , {4, "44"} };
bool Smash_It::Game::kinectControl = false;
sf::Clock Smash_It::Game::serverDelayClock;





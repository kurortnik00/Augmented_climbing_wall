#include "Labyrinth_Game.h"


Labyrinth::Game::Game(sf::RenderWindow &window)
	:_mainWindow(window)
{
	Labyrinth::Game::_gameState = Uninitialized;
	Labyrinth::Game::_selectedLevel = LEVEL_1;
	Labyrinth::Game::kinectControl = false;
}

void Labyrinth::Game::Start(myServer &server)	//инициализация объектов
{
	if (_gameState != Uninitialized) return;


	Game::Init();
	_kinectApplication.Run();

	_gameState = Game::ShowingMenu;		//Начинаем с заставки

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

	_gameState = Uninitialized;
	_gameObjectManager.RemoveAll();
}

bool Labyrinth::Game::IsExiting()//для остановки GameLoop()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

sf::RenderWindow& Labyrinth::Game::GetWindow()
{
	return Labyrinth::Game::_mainWindow;
}

CBodyBasics& Labyrinth::Game::getKinectApplication()
{
	return Game::_kinectApplication;
}

void Labyrinth::Game::GameLoop(myServer &server)
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
		//case Game::Custom:
		//{
		//	//ShowCustomScreen();
		//	break;
		//}
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
			break;
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


void Labyrinth::Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);   //Возврацает значение нажатой "кнопки", т.е. что делать дальше: Играть или выйти из игры
																//Внутри бесконечный цикл прерываемый по нажатию одной из "кнопок" или закрытию окна
																	

	switch (result)
	{
		case MainMenu::Exit:
			_gameState = Game::Exiting;
			break;
		case MainMenu::Play:
			_gameState = Game::Playing;
			Game::reInit();
			break;
		case MainMenu::NextLevel: 
			_selectedLevel = static_cast<SelectedLevel>((_selectedLevel + 1) % LAST);
			break;
		case MainMenu::PreviousLevel:
			if (_selectedLevel == LEVEL_1) _selectedLevel = static_cast<SelectedLevel>(LAST - 1);
			else _selectedLevel = static_cast<SelectedLevel>(_selectedLevel - 1);
			break;
	}
}

void Labyrinth::Game::Init() {

	Timer *time1 = new Timer();
	time1->Load("Labyrinth/font/11583.ttf");
	_gameObjectManager.Add("timer1", time1);

}

void Labyrinth::Game::levelInit()
{
	_gameObjectManager.Remove("level");

	switch (_selectedLevel)
	{
	case Game::LEVEL_1:
	{
		Level_1 *level_1 = new Level_1();
		_gameObjectManager.Add("level", level_1);
	}
		break;

	case Game::LEVEL_2:
	{
		Level_2 *level_2 = new Level_2();
		_gameObjectManager.Add("level", level_2);
		
	}
		break;

	case Game::LEVEL_3:
	{
		Level_3 *level_3 = new Level_3();
		_gameObjectManager.Add("level", level_3);
		
	}
		break;

	case Game::LEVEL_4:
	{
		Level_4 *level_4 = new Level_4();
		_gameObjectManager.Add("level", level_4);
		
	}
		break;

	case Game::CIRCLELvL:
	{
		CircleLvL *circleLvL = new CircleLvL();
		_gameObjectManager.Add("level", circleLvL);
	}
		break;

	case Game::LAST:
		break;
	default:
		break;
	}
}

void Labyrinth::Game::reInit()
{
	levelInit();
	_gameObjectManager.Get("timer1")->reInit();
	_gameObjectManager.Get("level")->setKinectControl(kinectControl);
	//_gameObjectManager.Get("winButton")->reInit();
	//_gameObjectManager.Get("startButton")->reInit();
}


void Labyrinth::Game::countIncriment() {

}

int Labyrinth::Game::getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// Равномерно распределяем рандомное число в нашем диапазоне
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

CBodyBasics Labyrinth::Game::_kinectApplication;






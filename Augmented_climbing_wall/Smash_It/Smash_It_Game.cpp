#include "Smash_It_Game.h"



Smash_It::Game::Game(sf::RenderWindow &window)
	:_mainWindow(window)
{
	Smash_It::Game::_gameState = Uninitialized;

	Config::loadConfig("Smash_It/Smash_It_config.txt");
	Smash_It::Game::targetCount = Config::smashIt_targets;				//max targets = 14 if you wana more change Init()
	Smash_It::Game::_font = Config::font;


	Smash_It::Game::TOP_List = { {6, "ASd"} , {5, "zzz"} , {1, "qq"} , {4, "44"} };
}


void Smash_It::Game::Start(myServer &server)	//������������� ��������
{
	if (_gameState != Uninitialized) return;


	Game::Init(targetCount);
	srand(static_cast<unsigned int>(time(0)));


	sf::Music music;//������� ������ ������
	music.openFromFile("Smash_It/sounds/merx-market-song.wav");//��������� ����
	music.setLoop(true);
	music.play();//������������� ������


	_gameState = Game::ShowingMenu;		//�������� � ����

	while (!IsExiting())
	{
		GameLoop(server);
		std::vector<int> data = getClientData(server);
		for (int i = 2; i < data.size(); i += 5)
		{
			if (data[i] == 4) _gameState = Game::Exiting;  //4 - BACK button presed (magick number from client)			
		}
	}

	_gameState = Uninitialized;
	_gameObjectManager.RemoveAll();
}

bool Smash_It::Game::IsExiting()//��� ��������� GameLoop()
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
	//_mainWindow.pollEvent(currentEvent);
	
	switch (_gameState)
	{
		
		case Game::ShowingMenu:
		{
			ShowMenu(server);
			break;
		}
		case Game::Playing:
		{
		
			
			_mainWindow.clear(sf::Color(0, 0, 0));
			
			_gameObjectManager.setAllPlased();
			
			_gameObjectManager.UpdateAll(currentEvent);		//��������� ��� �������
			_gameObjectManager.DrawAll(_mainWindow);		//������ ��� �������

			_mainWindow.display();

			if (currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;

			if (currentEvent.type == sf::Event::KeyPressed)
			{
				if (currentEvent.key.code == sf::Keyboard::Escape)		//����� �� ����� ���� � ���� �� ������� ESC
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
			GameOver_Screen(server);
		}
	}
}

void Smash_It::Game::ShowMenu(myServer &server)
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow, TOP_List, server);   //���������� �������� ������� "������", �.�. ��� ������ ������: ������ ��� ����� �� ����
																//������ ����������� ���� ����������� �� ������� ����� �� "������" ��� �������� ����
																	
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
	std::string targetFileNames[7] = {						
		"Smash_It/images/balloon_green.png", "Smash_It/images/balloon_blue.png", "Smash_It/images/balloon_orange.png", "Smash_It/images/balloon_pinck.png",
		"Smash_It/images/balloon_purple.png", "Smash_It/images/balloon_red.png", "Smash_It/images/balloon_yellow.png"
	};
	

	for (int i = 0; i < targ_count; i++) {
		Target *tar = new Target();
		int k = i;
		if (k > 6) k = k%6;
		tar->Load(targetFileNames[k]);
		_gameObjectManager.Add(std::to_string(i), tar);
	}

	Timer *time1 = new Timer();
	time1->Load(_font);
	_gameObjectManager.Add("timer1", time1);

	SmashCounter *counter = new SmashCounter();
	counter->Load(_font);
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
	// ���������� ������������ ��������� ����� � ����� ���������
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void Smash_It::Game::TOP_List_Update(myServer& server)
{

	sf::Event currentEvent;	
	std::string name = "";
	std::string scoreString = "Score: ";

	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << (int) _gameObjectManager.Get("counter")->getCount();
	scoreString += stream.str();
	

	clock.restart();
	bool flag = true;
	sf::Font font;
	font.loadFromFile(_font);
	sf::Image image;
	image.loadFromFile("Smash_It/images/restart.png");
	sf::Texture texture;
	texture.loadFromImage(image);
	while (flag)
	{
		//need for write name in top score
		/*_mainWindow.pollEvent(currentEvent);
		if (currentEvent.type == sf::Event::KeyPressed)
		{
			name += MyKeyboard::getChar();
		}*/
		
		_mainWindow.clear(sf::Color(0, 0, 0));

		sf::Text gameOverText("Game Over", font, Config::game_over_text_size);
		gameOverText.setPosition(Config::game_over_text_pos);

		sf::Text scoreText(scoreString, font, Config::game_over_score_size);
		scoreText.setPosition(Config::game_over_score_pos);

		sf::Text text(name, font, 150);
		text.setPosition(_mainWindow.getSize().x / 2 - 500, 400);
		

		_mainWindow.draw(text);
		_mainWindow.draw(scoreText);
		_mainWindow.draw(gameOverText);

		Colibration::drawColibrationShapes(myServer::SMASH_IT);

		std::vector<int> data = getClientData(server);
		for (int i = 2; i < data.size(); i += 5)
		{
			if (data[i] == 4) flag= false;  //4 - BACK button presed (magick number from client)			
		}

		
		if (clock.getElapsedTime().asSeconds() > 3)
		{
			sf::Image image;
			image.loadFromFile("Smash_It/images/restart.png");
			sf::Texture texture;
			texture.loadFromImage(image);
			sf::Sprite sprite;
			sprite.setTexture(texture);
			sprite.setScale(Config::restart_scale, Config::restart_scale);
			sf::Vector2f pos(Config::restart_pos);
			sprite.setPosition(pos);
			sf::Vector2f center(pos.x + texture.getSize().x * Config::restart_scale * Config::restart_scale, pos.y + texture.getSize().y * Config::restart_scale * Config::restart_scale);


			if (Cliker::getClik(center, texture.getSize().x * Config::restart_itarationRadius_scale, false, myServer::SMASH_IT, Modes::Type::AllBodies))
			{
				flag = false;
			}

			_mainWindow.draw(sprite);
		}

		

		_mainWindow.display();
	}
	if (TOP_List.size() > 4) TOP_List.erase(TOP_List.begin());
	TOP_List.insert(std::make_pair(_gameObjectManager.Get("counter")->getCount(), name));
}



void Smash_It::Game::GameOver_Screen(myServer& server)
{
	TOP_List_Update(server);
	_gameState = Game::ShowingMenu;
}


std::vector<int> Smash_It::Game::getClientData(myServer& server)
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






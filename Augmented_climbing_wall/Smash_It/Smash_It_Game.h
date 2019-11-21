#pragma once
#include "../stdafx.h"
#include "Smash_It_GameObjectManager.h"
#include "Smash_It_MainMenu.h"
#include "Smash_It_Target.h"
#include "Smash_It_Timer.h"
#include "Smash_It_SmashCounter.h"
#include "../myKeyboard.h"
#include "../server.h"
#include <random>
#include <iomanip>
#include <sstream>

namespace Smash_It
{

	class Game
	{

	public:

		Game(sf::RenderWindow& window);

		void Start(myServer &server);
		sf::RenderWindow& GetWindow();
		const int SCREEN_WIDTH = 1024;
		const int SCREEN_HEIGHT = 768;
		void countIncriment();

	private:
		bool IsExiting();
		void GameLoop(myServer &server);
		//void ShowSplashScreen();
		void ShowMenu(myServer &server);
		//void ShowCustomScreen();
		void Init(int targ_count);
		void reInit(int targ_count);
		int  targetCount;
		int getRandomNumber(int min, int max);
		void TOP_List_Update();
		void GameOver_Screen();

		enum GameState {
			Uninitialized, ShowingSplash, Paused,
			ShowingMenu, Playing, Exiting, GameOver
		};

		sf::Clock serverDelayClock;

		GameState _gameState;
		sf::RenderWindow & _mainWindow;
		Smash_It::GameObjectManager _gameObjectManager;
		int smashCount;
		std::set<std::pair<float, std::string>> TOP_List;
		bool kinectControl;

	};
}

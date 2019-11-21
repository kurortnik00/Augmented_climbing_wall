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
		static void Start(myServer &server);
		static sf::RenderWindow& GetWindow();
		const static int SCREEN_WIDTH = 1024;
		const static int SCREEN_HEIGHT = 768;
		static void countIncriment();

	private:
		static bool IsExiting();
		static void GameLoop(myServer &server);
		//static void ShowSplashScreen();
		static void ShowMenu(myServer &server);
		//static void ShowCustomScreen();
		static void Init(int targ_count);
		static void reInit(int targ_count);
		static int  targetCount;
		static int getRandomNumber(int min, int max);
		static void TOP_List_Update();
		static void GameOver_Screen();

		enum GameState {
			Uninitialized, ShowingSplash, Paused,
			ShowingMenu, Playing, Exiting, GameOver
		};

		static sf::Clock serverDelayClock;

		static GameState _gameState;
		static sf::RenderWindow _mainWindow;
		static Smash_It::GameObjectManager _gameObjectManager;
		static int smashCount;
		static std::set<std::pair<float, std::string>> TOP_List;
		static bool kinectControl;

	};
}

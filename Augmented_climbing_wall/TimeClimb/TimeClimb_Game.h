#pragma once
#include "../stdafx.h"
#include "TimeClimb_GameObjectManager.h"
#include "TimeClimb_MainMenu.h"
#include "TimeClimb_Target.h"
#include "TimeClimb_Timer.h"
#include "TimeClimb_CustomScreen.h"
#include "../myKeyboard.h"
#include <iomanip>
#include <sstream>
#include "../server.h"

namespace TimeClimb
{

	class Game
	{

	public:

		Game(sf::RenderWindow &window);

		void Start(myServer &server);
		sf::RenderWindow& GetWindow();
		const int SCREEN_WIDTH = 1024;
		const int SCREEN_HEIGHT = 768;

	private:
		bool IsExiting();
		void GameLoop(myServer &server);
		//void ShowSplashScreen();
		void ShowMenu(myServer& server);
		void ShowCustomScreen();
		void Init(int targ_count);
		void reInit(int targ_count);
		int targetCount;
		void TOP_List_Update();
		void GameOver_Screen();


		enum GameState {
			Uninitialized, ShowingSplash, Paused,
			ShowingMenu, Playing, Exiting, Custom, GameOver
		};

		sf::Clock serverDelayClock;

		GameState _gameState;
		sf::RenderWindow &_mainWindow;
		TimeClimb::GameObjectManager _gameObjectManager;
		std::set<std::pair<float, std::string>> TOP_List;
		bool kinectControl;
	};
}

#pragma once
#include "../stdafx.h"
#include "../BodyBasics.h"
#include "../server.h"
#include "Labyrinth_GameObjectManager.h"
#include "Labyrinth_MainMenu.h"
#include "circleLvL.h"
#include "Labyrinth_Timer.h"
#include "level_1.h"
#include "level_2.h"
#include "level_3.h"
#include "level_4.h"

namespace Labyrinth
{
	class Game
	{

	public:
		static void Start(myServer &server);
		static sf::RenderWindow& GetWindow();
		static CBodyBasics & getKinectApplication();
		const static int SCREEN_WIDTH = 1900;
		const static int SCREEN_HEIGHT = 1200;
		static void countIncriment();

	private:
		static bool IsExiting();
		static void GameLoop(myServer &server);
		//static void ShowSplashScreen();
		static void ShowMenu();
		//static void ShowCustomScreen();
		static void Init();
		static void reInit();
		static int getRandomNumber(int min, int max);
		static void levelInit();
		static std::vector<VisibleGameObject> levels;

		enum GameState {
			Uninitialized, ShowingSplash, Paused,
			ShowingMenu, Playing, Exiting, Custom
		};

		//LAST need for itarate all enums, and LAST not apear in itaration, its ounly recicle element
		enum SelectedLevel {
			LEVEL_1, LEVEL_2, LEVEL_3, LEVEL_4, CIRCLELvL, LAST
		};

		static sf::Clock serverDelayClock;

		static GameState _gameState;
		static sf::RenderWindow _mainWindow;
		static GameObjectManager _gameObjectManager;
		//static int smashCount;
		static SelectedLevel _selectedLevel;
		static bool kinectControl;
		static CBodyBasics _kinectApplication;
	};
}

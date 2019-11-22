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
		Game(sf::RenderWindow &window);

		void Start(myServer &server, int data);
		sf::RenderWindow& GetWindow();
		static CBodyBasics & getKinectApplication();
		const int SCREEN_WIDTH = 1920;
		const int SCREEN_HEIGHT = 1080;
		void countIncriment();

	private:
		bool IsExiting();
		void GameLoop(std::vector<int> data);
		//void ShowSplashScreen();
		void ShowMenu();
		//void ShowCustomScreen();
		void Init();
		void reInit();
		int getRandomNumber(int min, int max);
		void levelInit();
		std::vector<VisibleGameObject> levels;

		enum GameState {
			Uninitialized, ShowingSplash, Paused,
			ShowingMenu, Playing, Exiting, Custom
		};

		//LAST need for itarate all enums, and LAST not apear in itaration, its ounly recicle element
		enum SelectedLevel {
			LEVEL_1, LEVEL_2, LEVEL_3, LEVEL_4, CIRCLELvL, LAST
		};

		enum ButtonResult { 
			Nothing, Play, NextLevel, PreviousLevel, Exit, TopScore, setPos};

		sf::Clock serverDelayClock;

		GameState _gameState;
		sf::RenderWindow &_mainWindow;
		GameObjectManager _gameObjectManager;
		//int smashCount;
		SelectedLevel _selectedLevel;
		bool kinectControl;
		static CBodyBasics _kinectApplication;
	};
}

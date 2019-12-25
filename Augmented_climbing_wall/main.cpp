#include "Smash_It\Smash_It_Game.h"
#include "TimeClimb\TimeClimb_Game.h"
#include "Labyrinth\Labyrinth_Game.h"
#include "mainWindow.h"
#include "aerohockey/Aerohockey_starter.h"
#include "territory/Territory_starter.h"
#include "server.h"
#include "Cliker.h"
#include "Colibration.h"


int main()
{
	myServer *server = new myServer();
	//server->InitServer();
	Cliker::Init();
	bool flag_auto_colibration_finihed = false;


	enum dataType
	{
		gameState, game, presedButton, LvL
	};

	while (true)
	{
		//switch (server->getData()[gameState])
		switch (1)
		{
		case(myServer::EXIT):
			break;
		case(myServer::PLAY):
			MainWindow::getWindow().setMouseCursorVisible(true);
			//switch (server->getData()[game])
			switch (0)
			{
			case(myServer::SMASH_IT):
			{
				std::cout << "SMASh_it started \n";

				Smash_It::Game smash_It(MainWindow::getWindow());
				smash_It.Start(*server);
				break;
			}
			case(myServer::LABYRINTH):
			{
				std::cout << "LABYRINTH started \n";

				Labyrinth::Game labyrinth(MainWindow::getWindow());
				//labyrinth.Start(*server, server->getData()[LvL]);
				labyrinth.Start(*server, 3);
				break;
			}
			case(myServer::TIME_CLIMB):
			{
				std::cout << "TIME_CLIMB started \n";

				TimeClimb::Game timeClimb(MainWindow::getWindow());
				timeClimb.Start(*server);
				break;
			}
			case(myServer::AEROHOCKEY):
			{
				std::cout << "AEROHOCKEY started \n";

				// Load config before the game starts
				Aerohockey::Config::load("Aerohockey/config/Aerohockey_config.txt");

				Aerohockey::Starter aerohockey;
				aerohockey.start(*server);
				break;
			}
			case(myServer::TERRITORY):
			{
				std::cout << "TERRITORY started \n";

				Territory::Starter territory;
				territory.start(*server);
				break;
			}
			default:
				break;
			}
			break;
		default:
			break;
		case(myServer::AUTO_COLIBRATION):
			if (!flag_auto_colibration_finihed)
			{
				std::cout << "AUTO_COLIBRATION started \n";
				Colibration::init();
				Colibration::autoColibration();
				Cliker::reInit();
				flag_auto_colibration_finihed = true;
			}
			break;
		case(myServer::GAME_SELECTION):	
			MainWindow::getWindow().clear(sf::Color(0, 0, 0));
			MainWindow::getWindow().setMouseCursorVisible(false);
			MainWindow::getWindow().display();
			flag_auto_colibration_finihed = false;
			break;
		case(myServer::MANUAL_COLIBRATION):
			std::cout << "MANUAL_COLIBRATION started \n";
			if (server->getData()[2] == 0) Colibration::manualAdditionalColibration(*server);
			if (server->getData()[2] == 1) Colibration::manualEquationValuesColibration(*server);
			break;
		}
		
		//if (server->sendData(0) == 1) break;
	}
	
	server->endServer();

	delete(server);

	return 0;
}

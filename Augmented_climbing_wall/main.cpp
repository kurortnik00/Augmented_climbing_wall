#include "Smash_It\Smash_It_Game.h"
#include "TimeClimb\TimeClimb_Game.h"
#include "Labyrinth\Labyrinth_Game.h"
#include "mainWindow.h"
//#include "aerohockey/starter.h"
#include "server.h"


int main()
{
	std::cout << "tyt&";
	myServer *server = new myServer();
	server->InitServer();


	enum dataType
	{
		gameState, game, presedButton, LvL
	};

	while (true)
	{
		switch (server->getData()[gameState])
		{
		case(myServer::EXIT):
			break;
		case(myServer::PLAY):
			MainWindow::getWindow().setMouseCursorVisible(true);
			switch (server->getData()[game])
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
				labyrinth.Start(*server);
				break;
			}
			case(myServer::TIME_CLIMB):
				std::cout << "TIME_CLIMB started \n";
				TimeClimb::Game::Start(*server);
				break;
			case(myServer::AEROHOCKEY):
				std::cout << "AEROHOCKEY started \n";
				break;
			case(myServer::TERRITORY):
				std::cout << "TERRITORY started \n";
				break;
			default:
				break;
			}
			break;
		default:
			break;
		case(myServer::SCORE_BOARD):
			break;
		case(myServer::GAME_SELECTION):	
			MainWindow::getWindow().clear(sf::Color(0, 0, 0));
			MainWindow::getWindow().setMouseCursorVisible(false);
			MainWindow::getWindow().display();

			break;
		}
		
		//if (server->sendData(0) == 1) break;
	}
	
	server->endServer();

	delete(server);

	return 0;
}

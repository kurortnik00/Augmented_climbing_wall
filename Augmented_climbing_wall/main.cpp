#include "Smash_It\Smash_It_Game.h"
#include "TimeClimb\TimeClimb_Game.h"
#include "Labyrinth\Labyrinth_Game.h"
//#include "aerohockey/starter.h"
#include "server.h"


int main()
{
	std::cout << "tyt&";
	myServer *server = new myServer();
	server->InitServer();

	sf::RenderWindow blackWindow;
	//blackWindow.create(sf::VideoMode(1900, 1080), "window");

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
			blackWindow.close();
			switch (server->getData()[game])
			{
			case(myServer::SMASH_IT):
				std::cout << "SMASh_it started \n";
				Smash_It::Game::Start(*server);
				break;
			case(myServer::LABYRINTH):
				std::cout << "LABYRINTH started \n";
				Labyrinth::Game::Start(*server);
				break;
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
			if (!blackWindow.isOpen()) blackWindow.create(sf::VideoMode(1900, 1080), "window");
			break;
		}
		
		//if (server->sendData(0) == 1) break;
	}
	
	server->endServer();

	delete(server);

	return 0;
}

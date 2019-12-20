#pragma once
#include "Cliker.h"
#include "server.h"

class Colibration
{
public:
	Colibration();
	~Colibration();

	static void autoColibration();
	static void manualColibration(myServer::GAMES game);

private:

};


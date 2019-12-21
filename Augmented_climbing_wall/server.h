#pragma once
#include "stdafx.h"


class myServer
{
public:
	myServer();
	~myServer();


	int InitServer();
	std::vector<int> getData();
	int sendData(int data);
	void endServer();

	enum STATES
	{
		EXIT, PLAY, AUTO_COLIBRATION, GAME_SELECTION
	};

	enum GAMES
	{
		SMASH_IT, LABYRINTH, AEROHOCKEY, TIME_CLIMB, TERRITORY
	};
	enum LEVELS
	{
		LEVEL_1, LEVEL_2, LEVEL_3, LEVEL_4, LEVEL_5
	};

private:

	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	

};




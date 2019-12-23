#include "server.h"

/*
masege format from client:
1st byte - the menu state contains one of this integers:
	0 - exit	(not used)
	1 - game preporations
	3 - autocolibration
	4 - ready to play
	5 - manualCOlibration
2nd byte - the current game:
	0 - Smash_It
	//	1 - Time_Climb
	1 - Labyrinth
	2 - Aerohockey
	//4 - Territory
3rd byte - the action button pressed
	0 - Nothing
	1 - play_GameSelection
	2 - next
	3 - previous
	4 - back
	5 - TopScore (relevant to Smash_It, Time_Climb, Labyrinth)
	6 - set_Positions (relevant to Time_Climb)
	7 - play_ReadyToPlay
4rd byte - the current LvL in Labyrinth game
	0 - 1st lvl
	0 - 2st lvl
	0 - 3st lvl
	0 - 4st lvl
	0 - 5st lvl (circle lvl)
*/

myServer::myServer()
{
}

myServer::~myServer()
{
}

int myServer::InitServer()
{
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// No longer need server socket
	closesocket(ListenSocket);

	return 0;
}

std::vector<int>  myServer::getData()
{
	std::vector<int> vec = {};
	iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
	if (iResult > 0) {
		printf("Bytes received: %d\n", iResult);

		for (int i = 0; i < iResult; i++)
		{
			int k = (int)recvbuf[i] - '0';
			vec.push_back(k);
		}
		
		return vec;
	}
	return vec;
}

int myServer::sendData(int data)
{
	iSendResult = send(ClientSocket, recvbuf, data, 0);
	if (iSendResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}
	printf("Bytes sent: %d\n", iSendResult);
	return 0;
}

void myServer::endServer()
{
	closesocket(ClientSocket);
	WSACleanup();
}



#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <vector>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

#include <stdio.h>

#include <map>
#include <iostream>
#include <cassert>
#include <time.h>
#include <stdlib.h>
#include <cstdlib>
//#include "windows.h"

// Direct2D Header Files
#include <d2d1.h>

// Kinect Header files
#include <Kinect.h>

#pragma comment (lib, "d2d1.lib")



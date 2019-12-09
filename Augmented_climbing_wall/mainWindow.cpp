#include "mainWindow.h"

sf::RenderWindow &MainWindow::getWindow()
{
	return MainWindow::window;
}


//sf::RenderWindow MainWindow::window(sf::VideoMode(1920, 1080), "window", sf::Style::Fullscreen);
sf::RenderWindow MainWindow::window(sf::VideoMode(1366, 768), "window");
float MainWindow::SCREEN_WIDTH = 1920;
float MainWindow::SCREEN_HEIGHT = 1200;
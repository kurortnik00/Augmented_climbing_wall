
#include "Labyrinth_MainMenu.h"


void Labyrinth::TopScore::Show(std::set<std::pair<float, std::string>>& TOP_List)
{
	int scoresCount = 1;
	std::vector<sf::Text> plaersScore;
	sf::Font font;
	font.loadFromFile("Smash_It/font/11583.ttf");



	std::set<std::pair<float, std::string>>::reverse_iterator rit;

	for (rit = TOP_List.rbegin(); rit != TOP_List.rend(); ++rit)
	{

		std::string plaerScore_str = std::to_string(scoresCount) + ". " + rit->second + "       " + std::to_string((int)rit->first);
		sf::Text plaerScore(plaerScore_str, font, 150);
		plaerScore.setPosition(MainWindow::getWindow().getSize().x / 2 - 400, 200 + 100 * scoresCount);
		plaersScore.push_back(plaerScore);

		scoresCount++;
	}

	////Top score screen
	//bool flag = true;
	//while (flag)
	//{
		sf::Text topScore("TOP SCORE", font, 150);
		topScore.setPosition(MainWindow::getWindow().getSize().x / 2 - 400, 100);


		MainWindow::getWindow().clear(sf::Color(0, 0, 0));
		MainWindow::getWindow().draw(topScore);
		for (int i = 0; i < plaersScore.size(); i++)
		{
			MainWindow::getWindow().draw(plaersScore[i]);
		}

		MainWindow::getWindow().display();

	//}
}
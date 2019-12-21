#include "Colibration.h"

void Colibration::init()
{

	shape.setFillColor(sf::Color(0, 0, 0));
	radius = 50;
	shape.setRadius(radius);
	shape.setOutlineThickness(10);
	shape.setOutlineColor(sf::Color(250, 150, 100));

	
	font.loadFromFile("Smash_It/font/18123.ttf");

	clock.restart();
}

void Colibration::autoColibration(myServer& server)
{
	bool flag = true;
	while (flag)
	{
		MainWindow::getWindow().clear();
		sf::Event event;
		MainWindow::getWindow().pollEvent(event);
		
		switch (corner)
		{
		case Colibration::LEFT_TOP:
		{
			sf::Vector2f pos(50, 20);
			shape.setPosition(pos);
			MainWindow::getWindow().draw(shape);
			if (clock.getElapsedTime().asSeconds() > 5)
			{
				shape.setOutlineColor(sf::Color(250, 0, 0));
				float x = Cliker::kinectTranform_X_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(Limbs::Type::RIGHT_HAND, true).x);
				float y = Cliker::kinectTranform_Y_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(Limbs::Type::RIGHT_HAND, true).y);

				if (vectorClock.getElapsedTime().asMilliseconds() > 500)
				{
					x_sum_vector.push_back(x);
					y_sum_vector.push_back(y);
					vectorClock.restart();
				}

			}
			if (clock.getElapsedTime().asSeconds() > 15)
			{
				std::sort(x_sum_vector.begin(), x_sum_vector.end());
				Cliker::_sumValue.x = x_sum_vector[10] - pos.x;
				Cliker::_sumValue.y = y_sum_vector[10] - pos.y;

				x_sum_vector.clear();
				y_sum_vector.clear();
				corner = LEFT_BOTTOM;
				shape.setOutlineColor(sf::Color(250, 150, 100));
				clock.restart();
				
			}

			break;
		}
		case Colibration::LEFT_BOTTOM:
		{
			sf::Vector2f pos(50, 900);
			shape.setPosition(pos);
			MainWindow::getWindow().draw(shape);
			if (clock.getElapsedTime().asSeconds() > 5)
			{
				shape.setOutlineColor(sf::Color(250, 0, 0));
				float y = Cliker::kinectTranform_Y_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(Limbs::Type::RIGHT_HAND, true).y);
				if (vectorClock.getElapsedTime().asMilliseconds() > 500)
				{
					y_mult_vector.push_back(y);
					vectorClock.restart();
				}
			}
			if (clock.getElapsedTime().asSeconds() > 15)
			{
				std::sort(y_mult_vector.begin(), y_mult_vector.end());
				Cliker::_multValue.y = 1.4 * pos.y / (y_mult_vector[10] - Cliker::_sumValue.y);
				y_mult_vector.clear();

				shape.setOutlineColor(sf::Color(250, 150, 100));
				corner = RIGHT_TOP;
				clock.restart();
			}
			break;
		}
		case Colibration::RIGHT_TOP:
		{
			sf::Vector2f pos(1600, 20);
			shape.setPosition(pos);
			MainWindow::getWindow().draw(shape);
			if (clock.getElapsedTime().asSeconds() > 5)
			{
				shape.setOutlineColor(sf::Color(250, 0, 0));
				float x = Cliker::kinectTranform_X_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(Limbs::Type::RIGHT_HAND, true).x);
				if (vectorClock.getElapsedTime().asMilliseconds() > 500)
				{
					x_mult_vector.push_back(x);
					vectorClock.restart();
				}
			}
			if (clock.getElapsedTime().asSeconds() > 15)
			{
				std::sort(x_mult_vector.begin(), x_mult_vector.end());
				Cliker::_multValue.x = 2.4 * pos.x / (x_mult_vector[10] - Cliker::_sumValue.x);
				x_mult_vector.clear();

				shape.setOutlineColor(sf::Color(250, 150, 100));
				corner = RIGHT_BOTTOM;
				clock.restart();
			}
			break;
		}
		case Colibration::RIGHT_BOTTOM:
		{
			sf::Vector2f pos(1600, 900);
			shape.setPosition(pos);
			MainWindow::getWindow().draw(shape);

			if (clock.getElapsedTime().asSeconds() > 5)
			{
				shape.setOutlineColor(sf::Color(250, 0, 0));
				//TODO 
			//add formula for error

				float x = Cliker::kinectTranform_X_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(Limbs::Type::RIGHT_HAND, true).x);
				float y = Cliker::kinectTranform_Y_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(Limbs::Type::RIGHT_HAND, true).y);

				if (vectorClock.getElapsedTime().asMilliseconds() > 500)
				{
					x_error.push_back(x - pos.x);
					y_error.push_back(y - pos.y);
				}
			}
			if (clock.getElapsedTime().asSeconds() > 15)
			{
				
				for (int i = 0; i < x_error.size(); i++)
				{
					x_averError += std::abs(x_error[i]);
					y_averError += std::abs(y_error[i]);
				}
				x_averError = x_averError / x_error.size();
				y_averError = y_averError / y_error.size();
				x_error.clear();
				y_error.clear();

				corner = END;
				clock.restart();
			}
			break;
		}
		case END:
		{
			std::string endText = "colibration is over \n";
			endText += "Error x: ";
			endText += std::to_string(x_averError);
			endText += "\n";
			endText += "Error y: ";
			endText += std::to_string(y_averError);
			sf::Text text(endText, font, 100);
			text.setPosition(500,300);
			MainWindow::getWindow().draw(text);
			flag = false;
		}
			break;
		default:
			break;
		}
		MainWindow::getWindow().display();
	}
	
}

void Colibration::manualColibration(myServer& server, myServer::GAMES game)
{
	//TODO
}

Colibration::colibrationCorners Colibration::corner = Colibration::colibrationCorners::LEFT_TOP;
sf::CircleShape Colibration::shape;
sf::Clock Colibration::clock;
sf::Clock Colibration::vectorClock;
sf::Font Colibration::font;
float Colibration::radius;
std::vector<float> Colibration::x_sum_vector;
std::vector<float> Colibration::y_sum_vector;
std::vector<float> Colibration::x_mult_vector;
std::vector<float> Colibration::y_mult_vector;
std::vector<float> Colibration::x_error;
std::vector<float> Colibration::y_error;
float Colibration::x_averError = 0;
float Colibration::y_averError = 0;
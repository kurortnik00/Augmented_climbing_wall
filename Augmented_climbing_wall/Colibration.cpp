#include "Colibration.h"

void Colibration::init()
{

	shape.setFillColor(sf::Color(0, 0, 0));
	radius = 50;
	shape.setRadius(radius);
	shape.setOutlineThickness(10);
	shape.setOutlineColor(sf::Color(250, 150, 100));

	Cliker::_multValue = sf::Vector2f(0, 0);

	
	font.loadFromFile("Smash_It/font/18123.ttf");

	clock.restart();
}

void Colibration::autoColibration()
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

			std::ofstream colibrationFile;
			colibrationFile.open("autoColibration.txt");
			if (colibrationFile.is_open())
			{
				colibrationFile << "sumValue_x = " << std::to_string(Cliker::_sumValue.x) << std::endl;
				colibrationFile << "sumValue_y = " << std::to_string(Cliker::_sumValue.y) << std::endl;
				colibrationFile << "multValue_x = " << std::to_string(Cliker::_multValue.x) << std::endl;
				colibrationFile << "multValue_y = " << std::to_string(Cliker::_multValue.y) << std::endl;
			}
			colibrationFile.close();

		}
			break;
		default:
			break;
		}
		MainWindow::getWindow().display();
	}
	
}

enum dataType
{
	gameState, game, presedButton, LvL
};

std::vector<sf::Vector2f> Colibration::additionalValueColibration(std::vector<sf::Vector2f> limbsAditionValues, myServer& server)
{
	int button = 4;
	//server get data about pressed button (choise of action)
	//button = myServer::getData()...


	int i = 0;
	//server get data about pressed button (choise of limbs)
	//i = myServer::getData()....
	switch (button)
	{
	case Colibration::x_translation_up:
		limbsAditionValues[i].x += 0.01;
		break;
	case Colibration::x_translation_down:
		limbsAditionValues[i].x -= 1;
		break;
	case Colibration::y_translation_up:
		limbsAditionValues[i].y += 1;
		break;
	case Colibration::y_translation_down:
		limbsAditionValues[i].y -= 1;
		break;
	case Colibration::NOTHING:
		break;
	default:
		break;
	}
	return limbsAditionValues;
}

void Colibration::manualAdditionalColibration(myServer& server)
{
	while (1)
	{
		
		//switch (server.getData()[game])
		switch(0)
		{
		case myServer::SMASH_IT:
			Cliker::additional_sumValue_SmashIt = additionalValueColibration(Cliker::additional_sumValue_SmashIt, server);
			break;
		case myServer::LABYRINTH:
			Cliker::additional_sumValue_Labyrinth = additionalValueColibration(Cliker::additional_sumValue_Labyrinth, server);
			break;
		case myServer::AEROHOCKEY:
			Cliker::additional_sumValue_Aerohokey = additionalValueColibration(Cliker::additional_sumValue_Aerohokey, server);
			break;
		case myServer::TIME_CLIMB:
			break;
		case myServer::TERRITORY:
			break;
		default:
			break;
		}
	}
	std::ofstream colibrationFile;
	colibrationFile.open("manualColibration.txt");
	if (colibrationFile.is_open())
	{
		colibrationFile <<"sumValue_SmashIt_LEFT_HAND_x = " << std::to_string(Cliker::additional_sumValue_SmashIt[(int)Limbs::Type::LEFT_HAND].x) << std::endl;
		colibrationFile << "sumValue_SmashIt_LEFT_HAND_y = " << std::to_string(Cliker::additional_sumValue_SmashIt[(int)Limbs::Type::LEFT_HAND].y) << std::endl;
		colibrationFile << "sumValue_SmashIt_RIGHT_HAND_x = " << std::to_string(Cliker::additional_sumValue_SmashIt[(int)Limbs::Type::RIGHT_HAND].x) << std::endl;
		colibrationFile << "sumValue_SmashIt_RIGHT_HAND_y = " << std::to_string(Cliker::additional_sumValue_SmashIt[(int)Limbs::Type::RIGHT_HAND].y) << std::endl;
		colibrationFile << "sumValue_SmashIt_LEFT_FOOT_x = " << std::to_string(Cliker::additional_sumValue_SmashIt[(int)Limbs::Type::LEFT_FOOT].x) << std::endl;
		colibrationFile << "sumValue_SmashIt_LEFT_FOOT_y = " << std::to_string(Cliker::additional_sumValue_SmashIt[(int)Limbs::Type::LEFT_FOOT].y) << std::endl;
		colibrationFile << "sumValue_SmashIt_RIGHT_FOOT_x = " << std::to_string(Cliker::additional_sumValue_SmashIt[(int)Limbs::Type::RIGHT_FOOT].x) << std::endl;
		colibrationFile << "sumValue_SmashIt_RIGHT_FOOT_y = " << std::to_string(Cliker::additional_sumValue_SmashIt[(int)Limbs::Type::RIGHT_FOOT].y) << std::endl;

		colibrationFile << "sumValue_Labyrinth_LEFT_HAND_x = " << std::to_string(Cliker::additional_sumValue_Labyrinth[(int)Limbs::Type::LEFT_HAND].x) << std::endl;
		colibrationFile << "sumValue_Labyrinth_LEFT_HAND_y = " << std::to_string(Cliker::additional_sumValue_Labyrinth[(int)Limbs::Type::LEFT_HAND].y) << std::endl;
		colibrationFile << "sumValue_Labyrinth_RIGHT_HAND_x = " << std::to_string(Cliker::additional_sumValue_Labyrinth[(int)Limbs::Type::RIGHT_HAND].x) << std::endl;
		colibrationFile << "sumValue_Labyrinth_RIGHT_HAND_y = " << std::to_string(Cliker::additional_sumValue_Labyrinth[(int)Limbs::Type::RIGHT_HAND].y) << std::endl;
		colibrationFile << "sumValue_Labyrinth_LEFT_FOOT_x = " << std::to_string(Cliker::additional_sumValue_Labyrinth[(int)Limbs::Type::LEFT_FOOT].x) << std::endl;
		colibrationFile << "sumValue_Labyrinth_LEFT_FOOT_y = " << std::to_string(Cliker::additional_sumValue_Labyrinth[(int)Limbs::Type::LEFT_FOOT].y) << std::endl;
		colibrationFile << "sumValue_Labyrinth_RIGHT_FOOT_x = " << std::to_string(Cliker::additional_sumValue_Labyrinth[(int)Limbs::Type::RIGHT_FOOT].x) << std::endl;
		colibrationFile << "sumValue_Labyrinth_RIGHT_FOOT_y = " << std::to_string(Cliker::additional_sumValue_Labyrinth[(int)Limbs::Type::RIGHT_FOOT].y) << std::endl;

		colibrationFile << "sumValue_Aerohokey_LEFT_HAND_x = " << std::to_string(Cliker::additional_sumValue_Aerohokey[(int)Limbs::Type::LEFT_HAND].x) << std::endl;
		colibrationFile << "sumValue_Aerohokey_LEFT_HAND_y = " << std::to_string(Cliker::additional_sumValue_Aerohokey[(int)Limbs::Type::LEFT_HAND].y) << std::endl;
		colibrationFile << "sumValue_Aerohokey_RIGHT_HAND_x = " << std::to_string(Cliker::additional_sumValue_Aerohokey[(int)Limbs::Type::RIGHT_HAND].x) << std::endl;
		colibrationFile << "sumValue_Aerohokey_RIGHT_HAND_y = " << std::to_string(Cliker::additional_sumValue_Aerohokey[(int)Limbs::Type::RIGHT_HAND].y) << std::endl;
		colibrationFile << "sumValue_Aerohokey_LEFT_FOOT_x = " << std::to_string(Cliker::additional_sumValue_Aerohokey[(int)Limbs::Type::LEFT_FOOT].x) << std::endl;
		colibrationFile << "sumValue_Aerohokey_LEFT_FOOT_y = " << std::to_string(Cliker::additional_sumValue_Aerohokey[(int)Limbs::Type::LEFT_FOOT].y) << std::endl;
		colibrationFile << "sumValue_Aerohokey_RIGHT_FOOT_x = " << std::to_string(Cliker::additional_sumValue_Aerohokey[(int)Limbs::Type::RIGHT_FOOT].x) << std::endl;
		colibrationFile << "sumValue_Aerohokey_RIGHT_FOOT_y = " << std::to_string(Cliker::additional_sumValue_Aerohokey[(int)Limbs::Type::RIGHT_FOOT].y) << std::endl;
	}
	colibrationFile.close();
}

void Colibration::manualEquationValuesColibration(myServer &server)
{
	while (true)
	{
		enum BUTTONS
		{
			sumValue_x_up, sumValue_x_down, multValue_x_up, multValue_x_down,
			sumValue_y_up, sumValue_y_down, multValue_y_up, multValue_y_down
		};
		BUTTONS button;
		button = sumValue_x_up;
		//button = myServer::get....
		switch (button)
		{
		case sumValue_x_up:
			Cliker::_sumValue.x += 1;
			std::cout << "sumValue_x now: " << Cliker::_sumValue.x << std::endl;
			break;
		case sumValue_x_down:
			Cliker::_sumValue.x -= 1;
			std::cout << "sumValue_x now: " << Cliker::_sumValue.x << std::endl;
			break;
		case multValue_x_up:
			Cliker::_multValue.x += 0.1;
			std::cout << "multValue_x now: " << Cliker::_multValue.x << std::endl;
			break;
		case multValue_x_down:
			Cliker::_multValue.x -= 0.1;
			std::cout << "multValue_x now: " << Cliker::_multValue.x << std::endl;
			break;
		case sumValue_y_up:
			Cliker::_sumValue.y += 1;
			std::cout << "sumValue_y now: " << Cliker::_sumValue.y << std::endl;
			break;
		case sumValue_y_down:
			Cliker::_sumValue.y -= 1;
			std::cout << "sumValue_y now: " << Cliker::_sumValue.y << std::endl;
			break;
		case multValue_y_up:
			Cliker::_multValue.y += 0.1;
			std::cout << "multValue_y now: " << Cliker::_multValue.y << std::endl;
			break;
		case multValue_y_down:
			Cliker::_multValue.y -= 0.1;
			std::cout << "multValue_y now: " << Cliker::_multValue.y << std::endl;
			break;
		default:
			break;
		}
	}
	std::ofstream colibrationFile;
	colibrationFile.open("autoColibration.txt");
	if (colibrationFile.is_open())
	{
		colibrationFile << "sumValue_x = " << std::to_string(Cliker::_sumValue.x) << std::endl;
		colibrationFile << "sumValue_y = " << std::to_string(Cliker::_sumValue.y) << std::endl;
		colibrationFile << "multValue_x = " << std::to_string(Cliker::_multValue.x) << std::endl;
		colibrationFile << "multValue_y = " << std::to_string(Cliker::_multValue.y) << std::endl;
	}
	colibrationFile.close();
}


void Colibration::drawColibrationShapes(myServer::GAMES game)
{
	//add flag to undraw if debag is off
	if (true)
		return;

	for (int i = 0; i < (int)Limbs::Type::Count; i++)
	{
		sf::Vector2f xy = sf::Vector2f(Cliker::kinectTranform_X_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(static_cast<Limbs::Type>(i), true).x)
									 , Cliker::kinectTranform_Y_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(static_cast<Limbs::Type>(i), true).y));


		switch (game)
		{
		case myServer::SMASH_IT:
			xy += Cliker::additional_sumValue_SmashIt[i];
			break;
		case myServer::LABYRINTH:
			xy += Cliker::additional_sumValue_Labyrinth[i];
			break;
		case myServer::AEROHOCKEY:
			xy += Cliker::additional_multValue_Aerohokey[i];
			break;
		case myServer::TIME_CLIMB:
			break;
		case myServer::TERRITORY:
			break;
		default:
			break;
		}
		sf::CircleShape _shape1;
		float _radius = 30;
		_shape1.setFillColor(sf::Color(250, 50, 100));
		_shape1.setRadius(_radius);

		
		_shape1.setPosition(xy);
		MainWindow::getWindow().draw(_shape1);
	}	
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
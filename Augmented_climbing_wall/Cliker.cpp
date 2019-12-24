#include "Cliker.h"


void Cliker::Init()
{
	kinectApplication.Run();
	_trashHold = 1;
	Cliker::load("autoColibration.txt");
	Cliker::load("manualColibration.txt");
}

void Cliker::reInit()
{
	Cliker::load("autoColibration.txt");
	Cliker::load("manualColibration.txt");
}

template <typename T>
void read_param(std::string& line, std::string name, T& value)
{
	std::istringstream sin(line.substr(line.find("=") + 1));
	if (line.find(name) != -1)
	{
		sin >> value;
		std::cout << name << ": " << value << "\n";
	}
}

void Cliker::load(std::string path)
{
	// Open file if exists
	std::ifstream input(path);
	if (input.fail())
	{
		std::cout << "Failed to open config file: " << path << "\n";
		return;
	}

	std::cout << "Loading config from: " << path << "\n";

	// Read lines
	std::string line;
	while (std::getline(input, line))
	{
		// Comment lines should start with #
		if (line[0] == '#')
		{
			continue;
		}

		read_param(line, "sumValue_x", Cliker::_sumValue.x);
		read_param(line, "sumValue_y", Cliker::_sumValue.y);
		read_param(line, "multValue_x", Cliker::_multValue.x);
		read_param(line, "multValue_y", Cliker::_multValue.y);
		read_param(line, "trashHold", Cliker::_trashHold)

		read_param(line, "sumValue_SmashIt_LEFT_HAND_x", Cliker::additional_sumValue_SmashIt[(int)Limbs::Type::LEFT_HAND].x);
		read_param(line, "sumValue_SmashIt_LEFT_HAND_y", Cliker::additional_sumValue_SmashIt[(int)Limbs::Type::LEFT_HAND].y);
		read_param(line, "sumValue_SmashIt_RIGHT_HAND_x", Cliker::additional_sumValue_SmashIt[(int)Limbs::Type::RIGHT_HAND].x);
		read_param(line, "sumValue_SmashIt_RIGHT_HAND_y", Cliker::additional_sumValue_SmashIt[(int)Limbs::Type::RIGHT_HAND].y);
		read_param(line, "sumValue_SmashIt_LEFT_FOOT_x", Cliker::additional_sumValue_SmashIt[(int)Limbs::Type::LEFT_FOOT].x);
		read_param(line, "sumValue_SmashIt_LEFT_FOOT_y", Cliker::additional_sumValue_SmashIt[(int)Limbs::Type::LEFT_FOOT].y);
		read_param(line, "sumValue_SmashIt_RIGHT_FOOT_x", Cliker::additional_sumValue_SmashIt[(int)Limbs::Type::RIGHT_FOOT].x);
		read_param(line, "sumValue_SmashIt_RIGHT_FOOT_y", Cliker::additional_sumValue_SmashIt[(int)Limbs::Type::RIGHT_FOOT].y);

		read_param(line, "sumValue_Labyrinth_LEFT_HAND_x", Cliker::additional_sumValue_Labyrinth[(int)Limbs::Type::LEFT_HAND].x);
		read_param(line, "sumValue_Labyrinth_LEFT_HAND_y", Cliker::additional_sumValue_Labyrinth[(int)Limbs::Type::LEFT_HAND].y);
		read_param(line, "sumValue_Labyrinth_RIGHT_HAND_x", Cliker::additional_sumValue_Labyrinth[(int)Limbs::Type::RIGHT_HAND].x);
		read_param(line, "sumValue_Labyrinth_RIGHT_HAND_y", Cliker::additional_sumValue_Labyrinth[(int)Limbs::Type::RIGHT_HAND].y);
		read_param(line, "sumValue_Labyrinth_LEFT_FOOT_x", Cliker::additional_sumValue_Labyrinth[(int)Limbs::Type::LEFT_FOOT].x);
		read_param(line, "sumValue_Labyrinth_LEFT_FOOT_y", Cliker::additional_sumValue_Labyrinth[(int)Limbs::Type::LEFT_FOOT].y);
		read_param(line, "sumValue_Labyrinth_RIGHT_FOOT_x", Cliker::additional_sumValue_Labyrinth[(int)Limbs::Type::RIGHT_FOOT].x);
		read_param(line, "sumValue_Labyrinth_RIGHT_FOOT_y", Cliker::additional_sumValue_Labyrinth[(int)Limbs::Type::RIGHT_FOOT].y);

		read_param(line, "sumValue_Aerohokey_LEFT_HAND_x", Cliker::additional_sumValue_Aerohokey[(int)Limbs::Type::LEFT_HAND].x);
		read_param(line, "sumValue_Aerohokey_LEFT_HAND_y", Cliker::additional_sumValue_Aerohokey[(int)Limbs::Type::LEFT_HAND].y);
		read_param(line, "sumValue_Aerohokey_RIGHT_HAND_x", Cliker::additional_sumValue_Aerohokey[(int)Limbs::Type::RIGHT_HAND].x);
		read_param(line, "sumValue_Aerohokey_RIGHT_HAND_y", Cliker::additional_sumValue_Aerohokey[(int)Limbs::Type::RIGHT_HAND].y);
		read_param(line, "sumValue_Aerohokey_LEFT_FOOT_x", Cliker::additional_sumValue_Aerohokey[(int)Limbs::Type::LEFT_FOOT].x);
		read_param(line, "sumValue_Aerohokey_LEFT_FOOT_y", Cliker::additional_sumValue_Aerohokey[(int)Limbs::Type::LEFT_FOOT].y);
		read_param(line, "sumValue_Aerohokey_RIGHT_FOOT_x", Cliker::additional_sumValue_Aerohokey[(int)Limbs::Type::RIGHT_FOOT].x);
		read_param(line, "sumValue_Aerohokey_RIGHT_FOOT_y", Cliker::additional_sumValue_Aerohokey[(int)Limbs::Type::RIGHT_FOOT].y);
	}
}

BodyTracker& Cliker::getKinectApplication()
{
	return kinectApplication;
}


//button pressed for action after button clik, if false action after cursor in same position 
bool Cliker::getClik(sf::Vector2f center, float radius, bool buttonPress, myServer::GAMES game)
{
	sf::Event event;
	MainWindow::getWindow().pollEvent(event);

	tracking_Type tP = mainPointTimeAvarage;


	//_kinectControl set true or false in Game Init
	if (_kinectControl) {

		int joint_Count = 0;

		switch (tP)
		{
		case Cliker::allJoints:
			joint_Count = JointType_Count;
			if (kinectUpdateActions(joint_Count, tP, center, radius, game)) return true;
			break;
		case Cliker::mainPointAvarage:
			joint_Count = 4;
			if (kinectUpdateActions(joint_Count, tP, center, radius, game)) return true;
			break;
		case Cliker::allJointsTimeAvarage:
			joint_Count = JointType_Count;
			if (kinectUpdateActions(joint_Count, tP, center, radius, game)) return true;
		case Cliker::mainPointTimeAvarage:
			joint_Count = 4;
			if (kinectUpdateActions(joint_Count, tP, center, radius, game)) return true;
		default:
			break;
		}

	}

	else {
		if (buttonPress)
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{

				sf::Vector2f mouseVec(event.mouseButton.x, event.mouseButton.y);
				if ((dist2(center, mouseVec) < radius * radius))
				{
					return true;
				}

			}
		}
		else
		{
			sf::Vector2f mouseVec(sf::Mouse::getPosition(MainWindow::getWindow()).x, sf::Mouse::getPosition(MainWindow::getWindow()).y);
			if ((dist2(center, mouseVec) < radius * radius))
			{
				return true;
			}
		}

		
	}
	return false;
}

bool Cliker::getClik(float x, float y, float height, float width) 
{
	return true;
}



bool Cliker::Update(sf::Event& event, sf::Vector2f center)
{

	return true;
}




bool Cliker::kinectUpdateActions(int joint_Count, tracking_Type tP, sf::Vector2f center, float radius, myServer::GAMES game)
{
	kinectApplication.Update(false);
	for (int i = 0; i < joint_Count; i++) {

		switch (tP)
		{
		case Cliker::allJoints:
			joint_xy = sf::Vector2f(kinectApplication.getJointPointsXY(static_cast<Joints::Type>(i), true).x, kinectApplication.getJointPointsXY(static_cast<Joints::Type>(i), true).y);
			joint_z = kinectApplication.getJointDepthPoint(static_cast<Joints::Type>(i), true);
			break;
		case Cliker::mainPointAvarage:
			joint_xy = kinectApplication.getLimbPointsXY(static_cast<Limbs::Type>(i), true);
			joint_z = kinectApplication.getLimbDepthPoints(static_cast<Limbs::Type>(i), true);
			break;
		case Cliker::allJointsTimeAvarage:
			joint_xy = kinectApplication.getAllJoints_timeAveraged_PointsXY(i, true);
			joint_z = kinectApplication.getAllJoints_timeAveraged_DepthPoints(i, true);
			break;
		case Cliker::mainPointTimeAvarage:
			joint_xy = kinectApplication.get_arms_legs_timeAveraged_PointsXY(i, 0);
			joint_z = kinectApplication.get_arms_legs_timeAveraged_DepthPoints(i, 0);
		default:
			break;
		}


		joint_xy.x = kinectTranform_X_Cordinates(joint_xy.x); //translate to pixel
		joint_xy.y = kinectTranform_Y_Cordinates(joint_xy.y); //same

		//maby TODO add additional multiplaer "additional_mult..."
		switch (game)
		{
		case myServer::SMASH_IT:
			joint_xy += additional_sumValue_SmashIt[i];
			break;
		case myServer::LABYRINTH:
			joint_xy += additional_sumValue_Labyrinth[i];
			break;
		case myServer::AEROHOCKEY:
			joint_xy += additional_multValue_Aerohokey[i];
			break;
		case myServer::TIME_CLIMB:
			break;
		case myServer::TERRITORY:
			break;
		default:
			break;
		}



		if (joint_z >= _trashHold) {
			if (delayClock.getElapsedTime().asMilliseconds() > 0) {						//need instad (event.type == sf::Event::MouseButtonPressed) to avoid mass click to target
				if ((dist2(center, joint_xy) < radius * radius))
				{	
					delayClock.restart();
					return true;
				}
			}
		}
	}
	return false;
}


float Cliker::kinectTranform_X_Cordinates(float x)
{
	//return ((1920 - x * 1920 / 640) - 510) * 4.9 / 2.4;
	return (x - _sumValue.x) * _multValue.x / 2.4;
}

float Cliker::kinectTranform_Y_Cordinates(float y)
{
	//return (y * 1200 / 280 - 430) * 4 / 1.4;
	return (y - _sumValue.x) * _multValue.y / 1.4;
}

float Cliker::dist2(sf::Vector2f const& p1, sf::Vector2f const& p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

bool Cliker::_kinectControl = false;
float Cliker::_trashHold = 1;
BodyTracker Cliker::kinectApplication;
sf::Vector2f Cliker::joint_xy;
float Cliker::joint_z;
sf::Clock Cliker::delayClock;

sf::Vector2f Cliker::_sumValue = sf::Vector2f(0, 0);
sf::Vector2f Cliker::_multValue = sf::Vector2f(1, 1);
std::vector<sf::Vector2f> Cliker::additional_sumValue_SmashIt = { sf::Vector2f(0,0), sf::Vector2f(0,0), sf::Vector2f(0,0), sf::Vector2f(0,0) };
std::vector<sf::Vector2f> Cliker::additional_sumValue_Labyrinth = { sf::Vector2f(0,0), sf::Vector2f(0,0), sf::Vector2f(0,0), sf::Vector2f(0,0) };
std::vector<sf::Vector2f> Cliker::additional_sumValue_Aerohokey = { sf::Vector2f(0,0), sf::Vector2f(0,0), sf::Vector2f(0,0), sf::Vector2f(0,0) };
std::vector<sf::Vector2f> Cliker::additional_multValue_SmashIt = { sf::Vector2f(1,1), sf::Vector2f(1,1), sf::Vector2f(1,1), sf::Vector2f(1,1) };
std::vector<sf::Vector2f> Cliker::additional_multValue_Labyrinth = { sf::Vector2f(1,1), sf::Vector2f(1,1), sf::Vector2f(1,1), sf::Vector2f(1,1) };
std::vector<sf::Vector2f> Cliker::additional_multValue_Aerohokey = { sf::Vector2f(1,1), sf::Vector2f(1,1), sf::Vector2f(1,1), sf::Vector2f(1,1) };
#include "Cliker.h"


void Cliker::Init()
{
	kinectApplication.Run();
	_trashHold = 1.5;
 }

BodyTracker& Cliker::getKinectApplication()
{
	return kinectApplication;
}


//button pressed for action after button clik, if false action after cursor in same position 
bool Cliker::getClik(sf::Vector2f center, float radius, bool buttonPress)
{

	sf::Event event;
	MainWindow::getWindow().pollEvent(event);

	tracking_Type tP = mainPointAvarage;


	//_kinectControl set true or false in Game Init
	if (_kinectControl) {

		int joint_Count = 0;

		switch (tP)
		{
		case Cliker::allJoints:
			joint_Count = JointType_Count;
			if (kinectUpdateActions(joint_Count, tP, center, radius)) return true;
			break;
		case Cliker::mainPointAvarage:
			joint_Count = 4;
			if (kinectUpdateActions(joint_Count, tP, center, radius)) return true;
			break;
		case Cliker::allJointsTimeAvarage:
			joint_Count = JointType_Count;
			if (kinectUpdateActions(joint_Count, tP, center, radius)) return true;
		case Cliker::mainPointTimeAvarage:
			joint_Count = 4;
			if (kinectUpdateActions(joint_Count, tP, center, radius)) return true;
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




bool Cliker::kinectUpdateActions(int joint_Count, tracking_Type tP, sf::Vector2f center, float radius)
{
	sf::Vector2f joint_xy_2;
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
			joint_xy_2 = kinectApplication.getLimbPointsXY(static_cast<Limbs::Type>(i), false);
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
		joint_xy_2.x = kinectTranform_X_Cordinates(joint_xy.x); //same
		joint_xy_2.y = kinectTranform_Y_Cordinates(joint_xy.y); //same

		//some podgonian make left points lefter and right points righter
		switch (tP)
		{
		case Cliker::allJoints:
			break;
		case Cliker::mainPointAvarage:
			if (i == (int)Limbs::Type::RIGHT_FOOT || i == (int)Limbs::Type::RIGHT_HAND)
			{
				//joint_xy -= sf::Vector2f(20, 20);
			}
			else
			{
				joint_xy += sf::Vector2f(120, 0);
				joint_xy.x = joint_xy.x * 1.03;
				joint_xy.y = joint_xy.y * 1.15;
				joint_xy_2 += sf::Vector2f(120, 0);
				joint_xy_2.x = joint_xy.x * 1.03;
				joint_xy_2.y = joint_xy.y * 1.15;
			}
			break;
		case Cliker::allJointsTimeAvarage:
			break;
		case Cliker::mainPointTimeAvarage:
			if (i == (int)Limbs::Type::RIGHT_HAND || i == (int)Limbs::Type::RIGHT_FOOT)
			{
				joint_xy_2 -= sf::Vector2f(0, 0);
			}
			else
			{
				joint_xy += sf::Vector2f(160, 0);
				joint_xy.x = joint_xy.x * 1.1;
				joint_xy.y = joint_xy.y * 1.15;
				joint_xy_2 += sf::Vector2f(160, 0);
				joint_xy_2.x = joint_xy.x * 1.1;
				joint_xy_2.y = joint_xy.y * 1.15;

			}
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
				if ((dist2(center, joint_xy_2) < radius * radius))
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
	return (x - 360) * 3.9 / 2.55;
}

float Cliker::kinectTranform_Y_Cordinates(float y)
{
	//return (y * 1200 / 280 - 430) * 4 / 1.4;
	return (y - 280) * 3.7 / 1.55;
}

float Cliker::dist2(sf::Vector2f const& p1, sf::Vector2f const& p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

bool Cliker::_kinectControl = true;
float Cliker::_trashHold = 1;
BodyTracker Cliker::kinectApplication;
sf::Vector2f Cliker::joint_xy;
float Cliker::joint_z;
sf::Clock Cliker::delayClock;
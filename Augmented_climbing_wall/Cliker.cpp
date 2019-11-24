#include "Cliker.h"

void Cliker::Init()
{
	kinectApplication.Run();
	_trashHold = 1;
}

CBodyBasics& Cliker::getKinectApplication()
{
	return kinectApplication;
}

bool Cliker::getClik(sf::Vector2f center, float radius, sf::Event& event)
{
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
			if (kinectUpdateActions(joint_Count, tP, center,radius)) return true;
		default:
			break;
		}

	}

	else {
		if (event.type == sf::Event::MouseButtonPressed)
		{

			sf::Vector2f mouseVec(event.mouseButton.x, event.mouseButton.y);
			if ((dist2(center, mouseVec) < radius*radius))
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
	for (int i = 0; i < joint_Count; i++) {

		switch (tP)
		{
		case Cliker::allJoints:
			joint_xy = sf::Vector2f(kinectApplication.SkeletPointsXY(i).x, kinectApplication.SkeletPointsXY(i).y);
			joint_z = kinectApplication.DepthSkeletonPoints(i);
			break;
		case Cliker::mainPointAvarage:
			joint_xy = kinectApplication.arms_legs_pointAveraged_PointsXY(i);
			joint_z = kinectApplication.arms_legs_pointAveraged_DepthPoints(i);
			break;
		case Cliker::allJointsTimeAvarage:
			joint_xy = kinectApplication.allJoints_timeAveraged_PointsXY(i);
			joint_z = kinectApplication.allJoints_timeAveraged_DepthPoints(i);
			break;
		case Cliker::mainPointTimeAvarage:
			joint_xy = kinectApplication.arms_legs_timeAveraged_PointsXY(i);
			joint_z = kinectApplication.arms_legs_timeAveraged_DepthPoints(i);
		default:
			break;
		}


		joint_xy.x = kinectTranform_X_Cordinates(joint_xy.x); //translate to pixel
		joint_xy.y = kinectTranform_Y_Cordinates(joint_xy.y); //same



		if (joint_z >= _trashHold) {
			if (delayClock.getElapsedTime().asMilliseconds() > 500) {						//need instad (event.type == sf::Event::MouseButtonPressed) to avoid mass click to target
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
	return ((1920 - x * 1920 / 640) - 510) * 4.9 / 2.4;
}

float Cliker::kinectTranform_Y_Cordinates(float y)
{
	return (y * 1200 / 280 - 430) * 4 / 1.4;
}

float Cliker::dist2(sf::Vector2f const& p1, sf::Vector2f const& p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

bool Cliker::_kinectControl = true;
float Cliker::_trashHold = 1;
CBodyBasics Cliker::kinectApplication;
sf::Vector2f Cliker::joint_xy;
float Cliker::joint_z;
sf::Clock Cliker::delayClock;
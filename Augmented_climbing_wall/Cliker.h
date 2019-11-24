#pragma once
#include "stdafx.h"
#include "BodyBasics.h"
#include "Kinect.h"

class Cliker
{
public:
	//Cliker();
	//~Cliker();
	static void Init();

	static bool getClik(sf::Vector2f center, float radius, sf::Event& event);
	static bool getClik(float x, float y, float height, float width);
	static CBodyBasics &getKinectApplication();
	static float kinectTranform_X_Cordinates(float x);
	static float kinectTranform_Y_Cordinates(float y);
private:

	bool Update(sf::Event& event, sf::Vector2f center);

	static bool _kinectControl;
	
	static float dist2(sf::Vector2f const& p1, sf::Vector2f const& p2);


	enum tracking_Type
	{
		allJoints, mainPointAvarage, allJointsTimeAvarage, mainPointTimeAvarage
	};

	static bool kinectUpdateActions(int joint_Count, tracking_Type tT, sf::Vector2f center, float radius);
	static float _trashHold;				//depth from sensor where interaction starts
	static CBodyBasics kinectApplication;
	static sf::Vector2f joint_xy;
	static float joint_z;
	static sf::Clock delayClock;

	enum {
		SPINEBASE,
		SPINEMID,
		NECK,
		HEAD,
		SHOULDERLEFT,
		ELBOWLEFT,
		WRISTLEFT,
		HANDLEFT,
		SHOULDERRIGHT,
		ELBOWRIGHT,
		WRISTRIGHT,
		HANDRIGHT,
		HIPLEFT,
		KNEELEFT,
		ANKLELEFT,
		FOOTLEFT,
		HIPRIGHT,
		KNEERIGHT,
		ANKLERIGHT,
		FOOTRIGHT,
		SPINESHOULDER,
		HANDTIPLEFT,
		THUMBLEFT,
		HANDTIPRIGHT,
		THUMBRIGHT,
	};
};

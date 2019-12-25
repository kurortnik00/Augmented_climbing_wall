#pragma once
#include "stdafx.h"
#include "body_tracker.h"
#include "Kinect.h"
#include "mainWindow.h"
#include "server.h"
#include <fstream>
#include <sstream>
#include <string>

namespace Modes
{
	enum class Type
	{
		SingleBody,
		TwoBodies,
		AllBodies
	};
}

class Cliker
{
public:
	//Cliker();
	//~Cliker();
	static void Init();
	static void reInit();
	static void load(std::string path);

	static bool getClik(sf::Vector2f center, float radius, bool buttonPress, myServer::GAMES game, Modes::Type mode);
	static bool getClik(float x, float y, float height, float width);
	static BodyTracker &getKinectApplication();
	static float kinectTranform_X_Cordinates(float x);
	static float kinectTranform_Y_Cordinates(float y);

	static float getTrashHold();
	static void increaseTrashHold(float increaseValue);
	
	static sf::Vector2f _sumValue;
	static sf::Vector2f _multValue;
	static float _trashHold;
	static std::vector<sf::Vector2f> additional_sumValue_SmashIt;
	static std::vector<sf::Vector2f> additional_sumValue_Labyrinth;
	static std::vector<sf::Vector2f> additional_sumValue_Aerohokey;
	static std::vector<sf::Vector2f> additional_multValue_SmashIt;
	static std::vector<sf::Vector2f> additional_multValue_Labyrinth;
	static std::vector<sf::Vector2f> additional_multValue_Aerohokey;


private:

	bool Update(sf::Event& event, sf::Vector2f center);

	static bool _kinectControl;
	
	static float dist2(sf::Vector2f const& p1, sf::Vector2f const& p2);


	enum tracking_Type
	{
		allJoints, mainPointAvarage, allJointsTimeAvarage, mainPointTimeAvarage
	};

	static bool kinectUpdateActions(int joint_Count, tracking_Type tT, sf::Vector2f center, float radius, myServer::GAMES game, Modes::Type mode);
					//depth from sensor where interaction starts
	static bool getClickForBody(int body_id, int joint_Count, tracking_Type tP, sf::Vector2f center, float radius, myServer::GAMES game);
	static BodyTracker kinectApplication;
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

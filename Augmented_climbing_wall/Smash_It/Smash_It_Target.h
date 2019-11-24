#pragma once
#include "../StdAfx.h"
#include "Smash_It_Game.h"
#include <random>
#include "Smash_It_VisibleGameObject.h"
#include "../BodyBasics.h"
#include "Kinect.h"

namespace Smash_It
{
	class Target :
		public VisibleGameObject
	{
	public:
		Target();
		~Target();

		void Update(sf::Event& event);
		bool getState();
		bool getClickState();
		void setClickState(bool ans);
		void reInit();
		int getRandomNumber(int min, int max);
		//float dist2(sf::Vector2f const & p1, sf::Vector2f const & p2);
		void setKinectControl(bool kinectControl);		//use(set) in Game Init
		void Draw(sf::RenderWindow & window);


	private:
		bool isActive;
		bool hasClicked;
		float spriteX, spriteY, w, h;
		void animation();
		int animationFrame;
		sf::Clock animationClock;
		bool animationStart;
		void velocityAnimation();
		sf::Clock velocityAnimationClock;
		sf::Vector2f velocity;
		int windowSizeX, windowSizeY;
		void setRandomFlyStart();
		const sf::Vector2f constVelocity;
		float velocityAnimationTime;
		float animationTime;
		bool _kinectControl;
		//float kinectTranform_X_Cordinates(float x);
		//float kinectTranform_Y_Cordinates(float y);


		enum tracking_Type
		{
			allJoints, mainPointAvarage, allJointsTimeAvarage, mainPointTimeAvarage
		};

		//void kinectUpdateActions(int joint_Count, tracking_Type tT);
		float _trashHold;				//depth from sensor where interaction starts
		CBodyBasics kinectApplication;
		sf::Vector2f joint_xy;
		float joint_z;

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
}


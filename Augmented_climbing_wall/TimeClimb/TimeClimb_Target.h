#pragma once
#include "../StdAfx.h"
#include "TimeClimb_Target.h"
#include "TimeClimb_Game.h"
#include "TimeClimb_VisibleGameObject.h"
//#include "../BodyBasics.h"
#include "../Cliker.h"


namespace TimeClimb
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
		void setUnbreakable(bool ans);
		bool getUnbreakable();
		void setClickState(bool ans);
		void reInit();
		void Draw(sf::RenderWindow & window);
		//void setKinectControl(bool kinectControl);


	private:
		bool isActive;
		bool hasClicked;
		bool Unbreakable;		//������������� ����� ���� ���������� �� ��������
		float spriteX, spriteY, w, h;
		void animation();
		int animationFrame;
		sf::Clock animationClock;
		bool animationStart;
		float animationTime;
		//float dist2(sf::Vector2f const & p1, sf::Vector2f const & p2);

		//bool _kinectControl;
		//float _trashHold;
		//CBodyBasics kinectApplication;
		//sf::Vector2f joint_xy;
		//float joint_z;

		sf::Texture bodyTexture;
		sf::Sprite bodySprite;

		float kinectTranform_X_Cordinates(float x);
		float kinectTranform_Y_Cordinates(float y);
		/*enum tracking_Type
		{
			allJoints, mainPointAvarage, allJointsTimeAvarage, mainPointTimeAvarage
		};
		void kinectUpdateActions(int joint_Count, tracking_Type tT);*/


	};

}
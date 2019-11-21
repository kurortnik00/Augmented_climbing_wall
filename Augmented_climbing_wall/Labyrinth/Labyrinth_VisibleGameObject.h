#pragma once
#include "../stdafx.h"

namespace Labyrinth
{
	class VisibleGameObject
	{
	public:
		VisibleGameObject();
		virtual ~VisibleGameObject();

		virtual void Load(std::string filename);
		virtual void Draw(sf::RenderWindow & window);
		virtual void Update(sf::Event& event);
		virtual bool getClickState();
		virtual void setFinished(bool res);
		virtual bool getFinished();
		virtual void reInit();
		virtual void countIncroment();

		virtual void SetPosition(float x, float y);
		virtual sf::Vector2f GetPosition() const;
		virtual bool IsLoaded() const;


		virtual void setClickState(bool ans);
		virtual sf::Vector2f getCenter();

		virtual bool getWin();
		virtual void setWin(bool win);
		virtual void win(sf::Vector2f pos);
		virtual void lose(sf::Vector2f pos);

		void setPlased(bool res);
		bool getPlased();

		virtual void setStart(bool start);
		virtual bool getStart();

		virtual void setUnDraw(bool unDraw);
		virtual bool getUnDraw();

		virtual void setKinectControl(bool kinectControl);
		bool getKinectControll();

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

	protected:
		sf::Sprite& GetSprite();

	private:
		sf::Sprite  _sprite;
		sf::Texture _texture;
		sf::Image _image;
		std::string _filename;
		bool _isLoaded;
		bool _plased;
		bool _finished;
		bool _start;
		bool _unDraw;
		bool _kinectControl;
		bool _win;


	};
}

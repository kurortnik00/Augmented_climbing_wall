#pragma once
#include "../stdafx.h"

namespace Smash_It
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
		//virtual sf::Sprite& GetSprite();
		virtual void setScale(sf::Vector2f scale);
		virtual int getCount();

		virtual void SetPosition(float x, float y);
		virtual sf::Vector2f GetPosition() const;
		virtual bool IsLoaded() const;


		virtual void setClickState(bool ans);
		virtual sf::Vector2f getCenter();

		virtual float getFinishedTime();


		void setPlased(bool res);
		bool getPlased();



	protected:
		sf::Sprite& GetSprite();

	private:
		sf::Sprite  _sprite;
		sf::Texture _texture;
		sf::Image _image;
		std::string _filename;
		bool _isLoaded;
		bool plased;
		bool finished;
	};
}

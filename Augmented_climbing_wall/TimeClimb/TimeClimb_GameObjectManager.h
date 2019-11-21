#pragma once
#include "../stdafx.h"
#include "TimeClimb_VisibleGameObject.h"

namespace TimeClimb
{

	class GameObjectManager
	{
	public:
		GameObjectManager();
		~GameObjectManager();

		void Add(std::string name, VisibleGameObject* gameObject);
		void Remove(std::string name);
		int GetObjectCount() const;
		VisibleGameObject* Get(std::string name) const;

		void DrawAll(sf::RenderWindow& renderWindow);
		void UpdateAll(sf::Event& event);
		void setAllPlased();
		void RemoveAll();


	private:
		std::map<std::string, VisibleGameObject*> _gameObjects;

		struct GameObjectDeallocator
		{
			void operator()(const std::pair<std::string, VisibleGameObject*> & p) const
			{
				delete p.second;
			}
		};
	};
}

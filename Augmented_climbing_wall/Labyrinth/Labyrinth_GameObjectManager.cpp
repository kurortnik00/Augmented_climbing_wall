
#include "Labyrinth_GameObjectManager.h"


//Класс отвечающий за удаление, добавление и хранение объектов а так же за их Общую отрисовку и обновление 

Labyrinth::GameObjectManager::GameObjectManager()
{
}

Labyrinth::GameObjectManager::~GameObjectManager()
{
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}

void Labyrinth::GameObjectManager::Add(std::string name, VisibleGameObject* gameObject)
{
	_gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

void Labyrinth::GameObjectManager::Remove(std::string name)
{
	std::map<std::string, VisibleGameObject*>::iterator results = _gameObjects.find(name);
	if (results != _gameObjects.end())
	{
		delete results->second;
		_gameObjects.erase(results);
	}
}

void Labyrinth::GameObjectManager::RemoveAll()
{

	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());

	_gameObjects.erase(_gameObjects.begin(), _gameObjects.end());
}

Labyrinth::VisibleGameObject* Labyrinth::GameObjectManager::Get(std::string name) const
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
	if (results == _gameObjects.end())
		return NULL;
	return results->second;

}

int Labyrinth::GameObjectManager::GetObjectCount() const
{
	return _gameObjects.size();
}


void Labyrinth::GameObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		if (itr->second->getPlased()) itr->second->Draw(renderWindow);
		itr++;
	}
}

void Labyrinth::GameObjectManager::UpdateAll(sf::Event& event)
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	
	while (itr != _gameObjects.end())
	{
		itr->second->Update(event);

		if (itr->second->getStart()) {
			Labyrinth::Timer::start = true;
			Get("level")->setStart(true);
		}


		if (itr->second->getFinished() && !Labyrinth::Timer::getFinished()) {   ///Lose the levl
			Labyrinth::Timer::setFinished(true);
		}

		if (itr->second->getWin() && !Labyrinth::Timer::getFinished()) {		//Win the LVL
			
			Labyrinth::Timer::setFinished(true);
		}
		itr++;
	}
}

void Labyrinth::GameObjectManager::setAllPlased()
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->setPlased(true);
		itr++;
	}
}
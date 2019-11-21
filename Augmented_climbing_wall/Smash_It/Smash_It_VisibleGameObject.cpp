
#include "Smash_It_VisibleGameObject.h"

//Класс всех видимых объектов
Smash_It::VisibleGameObject::VisibleGameObject()
{
	_isLoaded = false;
	plased = false;
	finished = false;
}


Smash_It::VisibleGameObject::~VisibleGameObject()
{
}

void Smash_It::VisibleGameObject::Load(std::string filename)		//Простейшая загрузка спрайтов, загружается вся картинка целиком
{
	if (_image.loadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;

		_image.createMaskFromColor(sf::Color(255,255,255));
		_texture.loadFromImage(_image);
		//_texture.setSmooth(true);

		sf::Sprite sprite;
		_sprite.setTexture(_texture);

		_isLoaded = true;
	}
}

void Smash_It::VisibleGameObject::Draw(sf::RenderWindow & renderWindow)
{
	if (_isLoaded && !finished)
	{
		renderWindow.draw(_sprite);
	}
}

void Smash_It::VisibleGameObject::SetPosition(float x, float y)
{
	if (_isLoaded)
	{
		_sprite.setPosition(x, y);
	}
}

void Smash_It::VisibleGameObject::Update(sf::Event& event)
{

}


bool Smash_It::VisibleGameObject::getClickState()
{
	return false;
}

sf::Sprite& Smash_It::VisibleGameObject::GetSprite()
{
	return _sprite;
}

sf::Vector2f Smash_It::VisibleGameObject::GetPosition() const
{
	if (_isLoaded)
	{
		return _sprite.getPosition();
	}
	return sf::Vector2f();
}	

bool Smash_It::VisibleGameObject::IsLoaded() const
{
	return _isLoaded;
}


sf::Vector2f Smash_It::VisibleGameObject::getCenter() {
	sf::IntRect rect = _sprite.getTextureRect();
	return sf::Vector2f(_sprite.getPosition().x + rect.width / 2, _sprite.getPosition().y + rect.height / 2);
}


void Smash_It::VisibleGameObject::setFinished(bool res)
{
	finished = res;
}

bool Smash_It::VisibleGameObject::getFinished() {
	return false;
}

void Smash_It::VisibleGameObject::setPlased(bool res)
{
	plased = res;
}

bool Smash_It::VisibleGameObject::getPlased() {
	return plased;
}

void Smash_It::VisibleGameObject::setClickState(bool ans)
{

}
void Smash_It::VisibleGameObject::reInit() {

}

void Smash_It::VisibleGameObject::countIncroment() {

}

int Smash_It::VisibleGameObject::getCount() {
	return 4;
}

void Smash_It::VisibleGameObject::setScale(sf::Vector2f scale)
{
	_sprite.setScale(scale);
}

float Smash_It::VisibleGameObject::getFinishedTime()
{
	return 0;
}

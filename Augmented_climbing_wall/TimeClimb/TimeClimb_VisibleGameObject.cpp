#include "TimeClimb_VisibleGameObject.h"

//Класс всех видимых объектов
TimeClimb::VisibleGameObject::VisibleGameObject()
{
	_isLoaded = false;
	plased = false;
	finished = false;
	visible = true;
}


TimeClimb::VisibleGameObject::~VisibleGameObject()
{
}

void TimeClimb::VisibleGameObject::Load(std::string filename)		//Простейшая загрузка спрайтов, загружается вся картинка целиком
{
	if (_image.loadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;

		_image.createMaskFromColor(sf::Color(255, 255, 255));
		_texture.loadFromImage(_image);


		sf::Sprite sprite;
		_sprite.setTexture(_texture);

		_isLoaded = true;
	}
}

void TimeClimb::VisibleGameObject::Draw(sf::RenderWindow & renderWindow)
{
	if (_isLoaded && !finished)
	{
		renderWindow.draw(_sprite);
	}
}

void TimeClimb::VisibleGameObject::SetPosition(float x, float y)
{
	if (_isLoaded)
	{
		_sprite.setPosition(x, y);
	}
}

void TimeClimb::VisibleGameObject::Update(sf::Event& event)
{

}


bool TimeClimb::VisibleGameObject::getClickState()
{
	return false;
}

sf::Sprite& TimeClimb::VisibleGameObject::GetSprite()
{
	return _sprite;
}

sf::Vector2f TimeClimb::VisibleGameObject::GetPosition() const
{
	if (_isLoaded)
	{
		return _sprite.getPosition();
	}
	return sf::Vector2f();
}	

bool TimeClimb::VisibleGameObject::IsLoaded() const
{
	return _isLoaded;
}

float TimeClimb::VisibleGameObject::GetHeight() const
{
	return _sprite.getTexture()->getSize().y;
}

float TimeClimb::VisibleGameObject::GetWidth() const
{
	return _sprite.getTexture()->getSize().x;
}

sf::Rect<float> TimeClimb::VisibleGameObject::GetBoundingRect() const		//Прямоугольник для просчитывания взаиможействия
{
	sf::Vector2u size = _sprite.getTexture()->getSize();
	sf::Vector2f position = _sprite.getPosition();

	return sf::Rect<float>(
		position.x,
		position.y,
		size.x,
		size.y
		);
}

void TimeClimb::VisibleGameObject::Restart() {				//Для обновления игры, переопределяется в дочерних классах

}

void TimeClimb::VisibleGameObject::setUnbreakable(bool ans)
{

}

bool TimeClimb::VisibleGameObject::getUnbreakable()
{
	return true;
}

void TimeClimb::VisibleGameObject::setFinished(bool res)
{
	finished = res;
}

bool TimeClimb::VisibleGameObject::getFinished() {
	return false;
}

void TimeClimb::VisibleGameObject::setPlased(bool res)
{
	plased = res;
}

bool TimeClimb::VisibleGameObject::getPlased() {
	return plased;
}

void TimeClimb::VisibleGameObject::setClickState(bool ans)
{

}
void TimeClimb::VisibleGameObject::reInit() {

}

sf::Vector2f TimeClimb::VisibleGameObject::getCenter() {sf::IntRect rect = _sprite.getTextureRect();
	return sf::Vector2f(_sprite.getPosition().x + rect.width / 2, _sprite.getPosition().y + rect.height / 2);
}

float TimeClimb::VisibleGameObject::getFinishedTime()
{
	return -1;
}

bool TimeClimb::VisibleGameObject::getVisible()
{
	return visible;
}

void TimeClimb::VisibleGameObject::setVisible(bool vis)
{
	visible = vis;
}
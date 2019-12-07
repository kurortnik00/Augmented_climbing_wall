#include "Labyrinth_VisibleGameObject.h"

//Класс всех видимых объектов
Labyrinth::VisibleGameObject::VisibleGameObject()
{
	_isLoaded = false;
	_plased = false;
	_finished = false;
	_start = false;
	_unDraw = false;
	_kinectControl = false;
	_win = false;
}


Labyrinth::VisibleGameObject::~VisibleGameObject()
{
}

void Labyrinth::VisibleGameObject::Load(std::string filename)		//Простейшая загрузка спрайтов, загружается вся картинка целиком
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
		_texture.setSmooth(true);


		sf::Sprite sprite;
		_sprite.setTexture(_texture);

		_isLoaded = true;
	}
}

void Labyrinth::VisibleGameObject::Draw(sf::RenderWindow & renderWindow)
{
	if (_isLoaded && !_finished && !_unDraw)
	{
		renderWindow.draw(_sprite);
		
	}
}

void Labyrinth::VisibleGameObject::SetPosition(float x, float y)
{
	if (_isLoaded)
	{
		_sprite.setPosition(x, y);
	}
}

void Labyrinth::VisibleGameObject::Update(sf::Event& event)
{

}


bool Labyrinth::VisibleGameObject::getClickState()
{
	return false;
}

sf::Sprite& Labyrinth::VisibleGameObject::GetSprite()
{
	return _sprite;
}

sf::Vector2f Labyrinth::VisibleGameObject::GetPosition() const
{
	if (_isLoaded)
	{
		return _sprite.getPosition();
	}
	return sf::Vector2f();
}	

bool Labyrinth::VisibleGameObject::IsLoaded() const
{
	return _isLoaded;
}


sf::Vector2f Labyrinth::VisibleGameObject::getCenter() {
	sf::IntRect rect = _sprite.getTextureRect();
	return sf::Vector2f(_sprite.getPosition().x + rect.width / 2, _sprite.getPosition().y + rect.height / 2);
}

//void VisibleGameObject::Restart() {				//Для обновления игры, переопределяется в дочерних классах
//
//}

//void VisibleGameObject::setUnbreakable(bool ans)
//{
//
//}
//
//bool VisibleGameObject::getUnbreakable()
//{
//	return true;
//}

void Labyrinth::VisibleGameObject::setFinished(bool res)
{
	_finished = res;
}

bool Labyrinth::VisibleGameObject::getFinished() {
	return _finished;
}

void Labyrinth::VisibleGameObject::setPlased(bool res)
{
	_plased = res;
}

bool Labyrinth::VisibleGameObject::getPlased() {
	return _plased;
}

void Labyrinth::VisibleGameObject::setClickState(bool ans)
{

}
void Labyrinth::VisibleGameObject::reInit() {

}

void Labyrinth::VisibleGameObject::countIncroment() {

}

bool Labyrinth::VisibleGameObject::getWin() {
	return  _win;
}

void Labyrinth::VisibleGameObject::win(sf::Vector2f pos) {

}

void Labyrinth::VisibleGameObject::lose(sf::Vector2f pos) {

}

void Labyrinth::VisibleGameObject::setStart(bool start) {
	_start = start;
}

bool Labyrinth::VisibleGameObject::getStart() {
	return _start;
}

void Labyrinth::VisibleGameObject::setUnDraw(bool unDraw) {
	_unDraw = unDraw;
}

bool Labyrinth::VisibleGameObject::getUnDraw() {
	return _unDraw;
}

void Labyrinth::VisibleGameObject::setKinectControl(bool kinectControl) {
	_kinectControl = kinectControl;
}

bool Labyrinth::VisibleGameObject::getKinectControll() {
	return _kinectControl;
}

void Labyrinth::VisibleGameObject::setWin(bool win)
{
	_win = win;
}

void Labyrinth::VisibleGameObject::showTopScore()
{

}
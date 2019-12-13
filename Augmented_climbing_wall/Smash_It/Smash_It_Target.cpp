
#include "Smash_It_Target.h"



Smash_It::Target::Target()
	:constVelocity(0.8, 1)
{
	Load("Smash_It/images/balloon_green.png");
	assert(IsLoaded());
	isActive = true;
	hasClicked = false;
	spriteX = 0;
	spriteY = 0;
	w = 256;
	h = 256;
	VisibleGameObject::GetSprite().setTextureRect(sf::IntRect(spriteX, spriteY, w, h));
	animationFrame = 0;
	animationStart = false;
	animationClock.restart();
	velocityAnimationClock.restart();
	velocity = constVelocity;

	windowSizeX = 1900;
	windowSizeY = 1080;

	velocityAnimationTime = 0;
	animationTime = 0;

	shootBuffer.loadFromFile("Smash_It/sounds/balloon-pop.wav");
	shoot.setBuffer(shootBuffer);
}

Smash_It::Target::~Target()
{
}

bool Smash_It::Target::getState()
{
	return isActive;
}

bool Smash_It::Target::getClickState()
{
	return hasClicked;
}


void Smash_It::Target::setClickState(bool ans)
{

	hasClicked = ans;

}

void Smash_It::Target::Update(sf::Event& event) {

	
	if (Cliker::getClik(VisibleGameObject::getCenter(), 90, false))
	{
		if (!animationStart)
		{
			shoot.play();
			hasClicked = true;
			animationStart = true;
			animationClock.restart();

		}
		
	}

	velocityAnimation();
	animation();
	
}

void Smash_It::Target::Draw(sf::RenderWindow & window)
{
	sf::CircleShape _shape1;
	float _radius = 30;
	_shape1.setFillColor(sf::Color(0, 0, 0));
	_shape1.setRadius(_radius);
	_shape1.setOutlineThickness(10);
	_shape1.setOutlineColor(sf::Color(250, 50, 100));


	float x = Cliker::kinectTranform_X_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(Limbs::Type::RIGHT_FOOT, true).x);
	float y = Cliker::kinectTranform_Y_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(Limbs::Type::RIGHT_FOOT, true).y);
	_shape1.setPosition(sf::Vector2f(x, y));



	//float x1 = Cliker::kinectTranform_X_Cordinates(Cliker::getKinectApplication().getAllJoints_timeAveraged_PointsXY((int)Joints::Type::HANDRIGHT, true).x);

	sf::CircleShape _shape2;
	_shape2.setFillColor(sf::Color(0, 0, 0));
	_shape2.setRadius(_radius);
	_shape2.setOutlineThickness(10 );
	_shape2.setOutlineColor(sf::Color(250, 150, 100));
	x = Cliker::kinectTranform_X_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(Limbs::Type::LEFT_FOOT, true).x) +90;
	y = Cliker::kinectTranform_Y_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(Limbs::Type::LEFT_FOOT, true).y) -30;
	_shape2.setPosition(sf::Vector2f(x*1.03, y*1.15));

	

	//sf::CircleShape _shape3;
	//_shape3.setFillColor(sf::Color(0, 0, 0));
	//_shape3.setRadius(90);
	//_shape3.setOutlineThickness(10);
	//_shape3.setOutlineColor(sf::Color(250, 150, 100));
	//x = VisibleGameObject::GetPosition().x;
	//y = VisibleGameObject::GetPosition().y;
	//_shape3.setPosition(x, y);

	window.draw(_shape1);
	window.draw(_shape2);
//	window.draw(_shape3);

	//std::cout << x << "   " << y << "\n";

	VisibleGameObject::Draw(window); 
	
}

void Smash_It::Target::reInit() {
	isActive = true;
	hasClicked = false;
	spriteX = 0;
	spriteY = 0;
	VisibleGameObject::GetSprite().setTextureRect(sf::IntRect(spriteX, spriteY, w, h));
	VisibleGameObject::setFinished(false);
	setRandomFlyStart();
}

int Smash_It::Target::getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// ���������� ������������ ��������� ����� � ����� ���������
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}


void Smash_It::Target::animation() {
	if (!animationStart) {
		return;
	}
	if (animationFrame == 0)
	{
		spriteX = 0;
		spriteY = 0;
	}
	animationTime = animationClock.getElapsedTime().asMilliseconds();
	if (animationTime > 60) {				//animation speed
		spriteX = spriteX + 256;
		animationClock.restart();
		animationFrame++;
	}

	if (animationFrame == 5) {
		spriteX = 0;
		spriteY = 0;
		animationFrame = 0;
		animationStart = false;

		setRandomFlyStart();

	}
	VisibleGameObject::GetSprite().setTextureRect(sf::IntRect(spriteX, spriteY, w, h));
}


void Smash_It::Target::velocityAnimation()
{
	velocityAnimationTime = velocityAnimationClock.getElapsedTime().asMilliseconds();
	if (velocityAnimationTime > 30) {				//animation speed

		if (VisibleGameObject::GetPosition().x > windowSizeX + 100 || VisibleGameObject::GetPosition().y > windowSizeY + 100 ||
			VisibleGameObject::GetPosition().x < -w || VisibleGameObject::GetPosition().y < -h) {
			setRandomFlyStart();
		}

		VisibleGameObject::SetPosition(VisibleGameObject::GetPosition().x - velocity.x, VisibleGameObject::GetPosition().y - velocity.y);
		velocityAnimationClock.restart();
	}

}

void Smash_It::Target::setRandomFlyStart()				//����������� � ������������ �������� � ������ ������ �����
{
	int a = getRandomNumber(0, 2);
	int randVelocity = getRandomNumber(0, 10);
	int margin = 0;
	switch (a)
	{
	case 0:
		VisibleGameObject::SetPosition(getRandomNumber(-w, windowSizeX), windowSizeY);
		margin = windowSizeX / 2 - VisibleGameObject::GetPosition().x;					//Y velocity managed by spavn Y coordinates
		velocity.x = -4 * margin / windowSizeX + randVelocity / 10;
		break;
	case 1:
		VisibleGameObject::SetPosition(windowSizeX-100, getRandomNumber(windowSizeY - h / 3, windowSizeY / 3));  //wind from right to left
		velocity.x = constVelocity.x + (windowSizeY/2 - VisibleGameObject::GetPosition().y)/windowSizeY + 0.5 + randVelocity / 10;
		break;
	case 2:
		VisibleGameObject::SetPosition(-w +100, getRandomNumber(windowSizeY - h / 3, windowSizeY / 3));		//wind from lift to right
		velocity.x = -constVelocity.x +  (windowSizeY / 2 - VisibleGameObject::GetPosition().y) / windowSizeY -0.5 + randVelocity / 10;
		break;
	}
	velocity.y = constVelocity.y + randVelocity / 10;
}


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

	_trashHold = 1;	
	_kinectControl = true;
	kinectApplication.Run();

	

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

	tracking_Type tP = mainPointAvarage;
	//for shapes need change functions in Update

	//_kinectControl set true or false in Game Init
	if (_kinectControl) {

		int joint_Count = 0;

		switch (tP)
		{
		case Target::allJoints:
			joint_Count = JointType_Count;
			kinectUpdateActions(joint_Count, tP);
			break;
		case Target::mainPointAvarage:
			joint_Count = 4;
			kinectUpdateActions(joint_Count, tP);
			break;
		case Target::allJointsTimeAvarage:
			joint_Count = JointType_Count;
			kinectUpdateActions(joint_Count, tP);
		case Target::mainPointTimeAvarage:
			joint_Count = 4;
			kinectUpdateActions(joint_Count, tP);
		default:
			break;
		}
		
	}
	
	else {
		if (event.type == sf::Event::MouseButtonPressed)
		{

			sf::Vector2f mouseVec(event.mouseButton.x, event.mouseButton.y);
			if ((dist2(VisibleGameObject::getCenter(), mouseVec) < 8100))
			{
				hasClicked = true;
				animationStart = true;
				animationClock.restart();
			}

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
	float x = kinectTranform_X_Cordinates(kinectApplication.arms_legs_pointAveraged_PointsXY(CBodyBasics::RIGHT_ARM).x);
	float y = kinectTranform_Y_Cordinates(kinectApplication.arms_legs_pointAveraged_PointsXY(CBodyBasics::RIGHT_ARM).y);
	_shape1.setPosition(sf::Vector2f(x, y));

	sf::CircleShape _shape2;
	_shape2.setFillColor(sf::Color(0, 0, 0));
	_shape2.setRadius(_radius);
	_shape2.setOutlineThickness(10);
	_shape2.setOutlineColor(sf::Color(250, 150, 100));
	x = kinectTranform_X_Cordinates(kinectApplication.arms_legs_pointAveraged_PointsXY(CBodyBasics::LEFT_ARM).x);
	y = kinectTranform_Y_Cordinates(kinectApplication.arms_legs_pointAveraged_PointsXY(CBodyBasics::LEFT_ARM).y);
	_shape2.setPosition(sf::Vector2f(x, y));

	
	window.draw(_shape1);
	window.draw(_shape2);

	//std::cout << kinectApplication.arms_legs_timeAveraged_DepthPoints(CBodyBasics::LEFT_ARM) << "   " << kinectApplication.arms_legs_timeAveraged_DepthPoints(CBodyBasics::RIGHT_ARM) << "\n";
	//std::cout << kinectApplication.DepthSkeletonPoints(HANDLEFT) << "   " << kinectApplication.DepthSkeletonPoints(HANDRIGHT) << "\n";

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
	// Равномерно распределяем рандомное число в нашем диапазоне
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

float Smash_It::Target::dist2(sf::Vector2f const & p1, sf::Vector2f const & p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
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

void Smash_It::Target::setRandomFlyStart()				//РАЗОБРАТЬСЯ С НАПРАВЛЕНИЕМ СКОРОСТИ В СЛУЧАЕ СТАРТА СНИЗУ
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

//use(set) in Game Init
void Smash_It::Target::setKinectControl(bool kinectCOontrol) {
	_kinectControl = kinectCOontrol;
}

void Smash_It::Target::kinectUpdateActions(int joint_Count, tracking_Type tP)
{
	for (int i = 0; i < joint_Count; i++) {

		switch (tP)
		{
		case Target::allJoints:
			joint_xy = sf::Vector2f(kinectApplication.SkeletPointsXY(i).x, kinectApplication.SkeletPointsXY(i).y);
			joint_z = kinectApplication.DepthSkeletonPoints(i);
			break;
		case Target::mainPointAvarage:
			joint_xy = kinectApplication.arms_legs_pointAveraged_PointsXY(i);
			joint_z = kinectApplication.arms_legs_pointAveraged_DepthPoints(i);
			break;
		case Target::allJointsTimeAvarage:
			joint_xy = kinectApplication.allJoints_timeAveraged_PointsXY(i);
			joint_z = kinectApplication.allJoints_timeAveraged_DepthPoints(i);
			break;
		case Target::mainPointTimeAvarage:
			joint_xy = kinectApplication.arms_legs_timeAveraged_PointsXY(i);
			joint_z = kinectApplication.arms_legs_timeAveraged_DepthPoints(i);
		default:
			break;
		}
		

		joint_xy.x = kinectTranform_X_Cordinates(joint_xy.x); //translate to pixel
		joint_xy.y = kinectTranform_Y_Cordinates(joint_xy.y); //same



	if (joint_z >= _trashHold) {
			if (animationClock.getElapsedTime().asMilliseconds() > 100) {						//need instad (event.type == sf::Event::MouseButtonPressed) to avoid mass click to target
				if ((dist2(VisibleGameObject::getCenter(), joint_xy) < 8100))
				{
					hasClicked = true;
					animationStart = true;
					animationClock.restart();
				}
			}
		}
	}
}

float Smash_It::Target::kinectTranform_X_Cordinates(float x)
{
	return ((1920 - x * 1920 / 640) - 510)*4.9 / 2.4;
}

float Smash_It::Target::kinectTranform_Y_Cordinates(float y)
{
	return (y * 1200 / 280 - 430) * 4 / 1.4;
}
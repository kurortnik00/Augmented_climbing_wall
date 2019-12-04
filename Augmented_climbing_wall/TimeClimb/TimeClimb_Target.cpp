#include "TimeClimb_Target.h"


//Класс для примера, объекты класса спрайты которые уничтожаются по нажатию стрелки "влево"

TimeClimb::Target::Target()
{
	Load("TimeClimb/images/target2.png");
	assert(IsLoaded());
	isActive = true;
	hasClicked = false;
	Unbreakable = true;		//Невозможность клика пока предыдущие не кликнуты
	spriteX = 0;
	spriteY = 0;
	w = 256;
	h = 256;
	VisibleGameObject::GetSprite().setTextureRect(sf::IntRect(spriteX, spriteY, w, h));


	animationFrame = 0;
	animationStart = false;
	animationClock.restart();
	animationTime = 0;

	/*_kinectControl = false;
	_trashHold = 2;*/
	//kinectApplication.Run();

	bodyTexture.create(512, 424);
	bodySprite.setTexture(bodyTexture);
	//bodySprite.setScale(width_ / bodyTexture.getSize().x, height_ / bodyTexture.getSize().y);
	bodySprite.setScale(3.75, 2.4);

}

TimeClimb::Target::~Target()
{
}

bool TimeClimb::Target::getState()
{
	return isActive;
}

bool TimeClimb::Target::getClickState()
{
	return hasClicked;
}



void TimeClimb::Target::setUnbreakable(bool ans)
{
	Unbreakable = ans;
}

bool TimeClimb::Target::getUnbreakable()
{
	return Unbreakable;
}

void TimeClimb::Target::setClickState(bool ans)
{
	hasClicked = ans;
}

void TimeClimb::Target::Update(sf::Event& event) {

	Cliker::getKinectApplication().Update(true);
	bodyTexture.update(Cliker::getKinectApplication().getBodyMask());

	if (Cliker::getClik(VisibleGameObject::getCenter(), 90, false) && !hasClicked)
	{

		hasClicked = true;
		animationStart = true;
		animationClock.restart();

	}
	animation();
}

void TimeClimb::Target::Draw(sf::RenderWindow & window)
{
	sf::CircleShape _shape1;
	float _radius = 30;
	_shape1.setFillColor(sf::Color(0, 0, 0));
	_shape1.setRadius(_radius);
	_shape1.setOutlineThickness(10);
	_shape1.setOutlineColor(sf::Color(250, 50, 100));
	float x = Cliker::kinectTranform_X_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(Limbs::Type::RIGHT_HAND, true).x);
	float y = Cliker::kinectTranform_Y_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(Limbs::Type::RIGHT_HAND, true).y);
	_shape1.setPosition(sf::Vector2f(x, y));

	sf::CircleShape _shape2;
	_shape2.setFillColor(sf::Color(0, 0, 0));
	_shape2.setRadius(_radius);
	_shape2.setOutlineThickness(10);
	_shape2.setOutlineColor(sf::Color(250, 150, 100));
	x = Cliker::kinectTranform_X_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(Limbs::Type::LEFT_HAND, true).x);
	y = Cliker::kinectTranform_Y_Cordinates(Cliker::getKinectApplication().getLimbPointsXY(Limbs::Type::LEFT_HAND, true).y);
	_shape2.setPosition(sf::Vector2f(x, y));


	

	window.draw(bodySprite);
	window.draw(_shape1);
	window.draw(_shape2);
	

	//std::cout << kinectApplication.arms_legs_timeAveraged_DepthPoints(CBodyBasics::LEFT_ARM) << "   " << kinectApplication.arms_legs_timeAveraged_DepthPoints(CBodyBasics::RIGHT_ARM) << "\n";
	//std::cout << kinectApplication.DepthSkeletonPoints(HANDLEFT) << "   " << kinectApplication.DepthSkeletonPoints(HANDRIGHT) << "\n";

	VisibleGameObject::Draw(window);
	
}

void TimeClimb::Target::reInit() {
	isActive = true;
	hasClicked = false;
	Unbreakable = true;		//Невозможность клика пока предыдущие не кликнуты
	spriteX = 0;
	spriteY = 0;
	w = 256;
	h = 256;
	VisibleGameObject::GetSprite().setTextureRect(sf::IntRect(spriteX, spriteY, w, h));
	VisibleGameObject::setFinished(false);

	animationFrame = 0;
	animationStart = false;
	animationClock.restart();
	animationTime = 0;
}


void TimeClimb::Target::animation() {
	if (!animationStart) {
		return;
	}
	if (animationFrame == 0)
	{
		spriteX = 0;
		spriteY = 768;
	}
	animationTime = animationClock.getElapsedTime().asMilliseconds();
	if (animationTime > 30) {				//animation speed
		spriteX = spriteX + 256;
		animationClock.restart();
		animationFrame++;
	}

	if (animationFrame == 4) {
		spriteX = 0;
		spriteY = 1024;
	}
	if (animationFrame == 7) {

		animationFrame = 0;
		animationStart = false;

	}
	VisibleGameObject::GetSprite().setTextureRect(sf::IntRect(spriteX, spriteY, w, h));


}

//float TimeClimb::Target::dist2(sf::Vector2f const & p1, sf::Vector2f const & p2)
//{
//	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
//}


//void TimeClimb::Target::kinectUpdateActions(int joint_Count, tracking_Type tP)
//{
//	
//}

//void TimeClimb::Target::setKinectControl(bool kinectCOontrol) {
//
//	_kinectControl = kinectCOontrol;
//}

float TimeClimb::Target::kinectTranform_X_Cordinates(float x)
{
	return ((1920 - x * 1920 / 640) - 510)*4.9 / 2.4;
}

float TimeClimb::Target::kinectTranform_Y_Cordinates(float y)
{
	return (y * 1200 / 280 - 430) * 4 / 1.4;
}


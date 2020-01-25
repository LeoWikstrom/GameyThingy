#include "Player.h"

Player::Player() : Object()
{
	this->speed = 50;
	this->health = 3;
}

Player::Player(float speed, int health, sf::Vector2i keyFrameSize, sf::Vector2i spriteSheetSize, sf::Vector2i currentKeyFrame, sf::Vector2f startPosition, float animationSpeed, float keyFrameDuration, std::string fileName) : Object(keyFrameSize,
	spriteSheetSize,
	currentKeyFrame,
	startPosition,
	animationSpeed,
	keyFrameDuration,
	fileName)
{
	this->speed = speed;
	this->health = health;
	this->fullscreenMultiplier = 1;
}

Player::~Player()
{
}

void Player::Update(float dt, bool isFullscreen)
{
	if (isFullscreen && !wasFullscreen)
	{
		this->speed *= 10.f;
		this->fullscreenMultiplier = 10;
		
	}
	else if (!isFullscreen && wasFullscreen)
	{
		this->speed *= 0.1f;
		this->fullscreenMultiplier = 1;
	}

	this->Object::Update(dt, isFullscreen);


	wasFullscreen = isFullscreen;

	bool isWpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool isApressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool isSpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool isDpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	bool isSpacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if (isWpressed && !isApressed && !isDpressed && !isSpressed) //Move up
	{
		if (!wasWpressed)
			this->setCurrentKeyFrameX(0);
		this->setCurrentKeyFrameY(1);
		this->getSprite()->move(0, -speed*dt);
		this->weapon.getSprite()->setPosition(-500, -500);
		this->weapon.setCurrentKeyFrameX(3);
	}
	else if (isApressed && !isWpressed && !isSpressed && !isDpressed) //Move left
	{
		if (!wasApressed)
			this->setCurrentKeyFrameX(0);
		this->setCurrentKeyFrameY(3);
		this->getSprite()->move(-speed*dt, 0);
		this->weapon.getSprite()->setPosition(-500, -500);
		this->weapon.setCurrentKeyFrameX(3);
	}
	else if (isSpressed && !isApressed && !isDpressed && !isWpressed) //Move down
	{
		if (!wasSpressed)
			this->setCurrentKeyFrameX(0);
		this->setCurrentKeyFrameY(0);
		this->getSprite()->move(0, speed*dt);
		this->weapon.getSprite()->setPosition(-500, -500);
		this->weapon.setCurrentKeyFrameX(3);
	}
	else if (isDpressed && !isWpressed && !isSpressed && !isApressed) //Move right
	{
		if (!wasDpressed)
			this->setCurrentKeyFrameX(0);
		this->setCurrentKeyFrameY(2);
		this->getSprite()->move(speed*dt, 0);
		this->weapon.getSprite()->setPosition(-500, -500);
		this->weapon.setCurrentKeyFrameX(3);
	}
	else if (isWpressed && isApressed) //Move up-left
	{
		if (!wasWpressed && !wasApressed)
			this->setCurrentKeyFrameX(0);
		if (!wasWpressed)
			this->setCurrentKeyFrameY(3);
		if (!wasApressed)
			this->setCurrentKeyFrameY(1);
		this->getSprite()->move(-sqrt(pow(speed, 2)/2)*dt, -sqrt(pow(speed, 2)/2)*dt);
		this->weapon.getSprite()->setPosition(-500, -500);
		this->weapon.setCurrentKeyFrameX(3);
	}
	else if (isWpressed && isDpressed) //Move up-right
	{
		if (!wasWpressed && !wasDpressed)
			this->setCurrentKeyFrameX(0);
		if (!wasWpressed)
			this->setCurrentKeyFrameY(2);
		if(!wasDpressed)
			this->setCurrentKeyFrameY(1);
		this->getSprite()->move(sqrt(pow(speed, 2) / 2)*dt, -sqrt(pow(speed, 2) / 2)*dt);
		this->weapon.getSprite()->setPosition(-500, -500);
		this->weapon.setCurrentKeyFrameX(3);
	}
	else if (isSpressed && isApressed) //Move down-left
	{
		if (!wasSpressed && !wasApressed)
			this->setCurrentKeyFrameX(0);
		if (!wasSpressed)
			this->setCurrentKeyFrameY(3);
		if (!wasApressed)
			this->setCurrentKeyFrameY(0);
		this->getSprite()->move(-sqrt(pow(speed, 2) / 2)*dt, sqrt(pow(speed, 2) / 2)*dt);
		this->weapon.getSprite()->setPosition(-500, -500);
		this->weapon.setCurrentKeyFrameX(3);
	}
	else if (isSpressed && isDpressed) //Move down-right
	{
		if (!wasSpressed && !wasDpressed)
			this->setCurrentKeyFrameX(0);
		if (!wasSpressed)
			this->setCurrentKeyFrameY(2);
		if (!wasDpressed)
			this->setCurrentKeyFrameY(0);
		this->getSprite()->move(sqrt(pow(speed, 2) / 2)*dt, sqrt(pow(speed, 2) / 2)*dt);
		this->weapon.setCurrentKeyFrameX(3);
		this->weapon.getSprite()->setPosition(-500, -500);
	}
	else if (isApressed && isDpressed)
	{
		if (!wasApressed && !wasDpressed)
			this->setCurrentKeyFrameX(0);
		if (!wasApressed)
			this->setCurrentKeyFrameY(2);
		if (!wasDpressed)
			this->setCurrentKeyFrameY(3);
		this->weapon.setCurrentKeyFrameX(3);
		this->weapon.getSprite()->setPosition(-500, -500);
	}
	else if (isWpressed && isSpressed)
	{
		if (!wasWpressed && !wasSpressed)
			this->setCurrentKeyFrameX(0);
		if (!wasWpressed)
			this->setCurrentKeyFrameY(0);
		if (!wasSpressed)
			this->setCurrentKeyFrameY(1);
		this->weapon.setCurrentKeyFrameX(3);
		this->weapon.getSprite()->setPosition(-500, -500);
	}
	else if (isSpacePressed && !isWpressed && !isApressed && !isSpressed && !isDpressed)
	{
		if (!wasSpacePressed || wasWpressed || wasApressed || wasSpressed || wasDpressed)
		{
			this->setCurrentKeyFrameX(3);
			this->weapon.setCurrentKeyFrameX(3);
		}

		this->Object::Update(dt, isFullscreen);
		this->weapon.Update(dt, isFullscreen);
		if (this->getCurrentKeyFrameY() == 0 || this->getCurrentKeyFrameY() == 4)
		{
			if (this->getCurrentKeyFrameY() == 0)
				this->weapon.setCurrentKeyFrameX(3);

			this->setCurrentKeyFrameY(4);
			this->weapon.setCurrentKeyFrameY(0);
			if (this->getCurrentKeyFrameX() == 0)
			{
				this->weapon.getSprite()->setPosition(-500, -500);
				this->weapon.getSprite()->setRotation(-90);
			}
			else if (this->getCurrentKeyFrameX() == 1)
				this->weapon.getSprite()->setPosition(this->getSprite()->getPosition().x - 16 * fullscreenMultiplier, this->getSprite()->getPosition().y + 17 * fullscreenMultiplier);
			else if (this->getCurrentKeyFrameX() == 2)
				this->weapon.getSprite()->setPosition(this->getSprite()->getPosition().x - 14 * fullscreenMultiplier, this->getSprite()->getPosition().y + 27 * fullscreenMultiplier);
			else if (this->getCurrentKeyFrameX() == 3)
			{
				this->weapon.getSprite()->setPosition(this->getSprite()->getPosition().x + 4 * fullscreenMultiplier, this->getSprite()->getPosition().y + 14 * fullscreenMultiplier);
				this->weapon.getSprite()->setRotation(0);
			}
		}
		else if (this->getCurrentKeyFrameY() == 1 || this->getCurrentKeyFrameY() == 5)
		{
			if (this->getCurrentKeyFrameY() == 1)
				this->weapon.setCurrentKeyFrameX(3);

			this->setCurrentKeyFrameY(5);
			this->weapon.setCurrentKeyFrameY(1);
			if (this->getCurrentKeyFrameX() == 0)
			{
				this->weapon.getSprite()->setPosition(-500, -500);
				this->weapon.getSprite()->setRotation(90);
			}
			else if (this->getCurrentKeyFrameX() == 1)
				this->weapon.getSprite()->setPosition(this->getSprite()->getPosition().x + 34 * fullscreenMultiplier, this->getSprite()->getPosition().y);
			else if (this->getCurrentKeyFrameX() == 2)
				this->weapon.getSprite()->setPosition(this->getSprite()->getPosition().x + 30 * fullscreenMultiplier, this->getSprite()->getPosition().y - 8 * fullscreenMultiplier);
			else if (this->getCurrentKeyFrameX() == 3)
			{
				this->weapon.getSprite()->setPosition(this->getSprite()->getPosition().x - 2 * fullscreenMultiplier, this->getSprite()->getPosition().y -20 * fullscreenMultiplier);
				this->weapon.getSprite()->setRotation(0);
			}
		}
		else if (this->getCurrentKeyFrameY() == 2 || this->getCurrentKeyFrameY() == 6)
		{
			if (this->getCurrentKeyFrameY() == 2)
				this->weapon.setCurrentKeyFrameX(3);

			this->setCurrentKeyFrameY(6);
			this->weapon.setCurrentKeyFrameY(2);
			if(this->getCurrentKeyFrameX() == 0)
			{
				this->weapon.getSprite()->setPosition(-500, -500);
				this->weapon.getSprite()->setRotation(0);
			}
			else if (this->getCurrentKeyFrameX() == 1)
				this->weapon.getSprite()->setPosition(this->getSprite()->getPosition().x + 5 * fullscreenMultiplier, this->getSprite()->getPosition().y - 15 * fullscreenMultiplier);
			else if (this->getCurrentKeyFrameX() == 2)
				this->weapon.getSprite()->setPosition(this->getSprite()->getPosition().x + 13 * fullscreenMultiplier, this->getSprite()->getPosition().y - 11 * fullscreenMultiplier);
			else if (this->getCurrentKeyFrameX() == 3)
			{
				this->weapon.getSprite()->setPosition(this->getSprite()->getPosition().x + 35 * fullscreenMultiplier, this->getSprite()->getPosition().y + 5 * fullscreenMultiplier);
				this->weapon.getSprite()->setRotation(90);
			}
		}
		else if (this->getCurrentKeyFrameY() == 3 || this->getCurrentKeyFrameY() == 7)
		{
			if (this->getCurrentKeyFrameY() == 3)
				this->weapon.setCurrentKeyFrameX(3);

			this->setCurrentKeyFrameY(7);
			this->weapon.setCurrentKeyFrameY(3);
			if (this->getCurrentKeyFrameX() == 0)
			{
				this->weapon.getSprite()->setPosition(-500, -500);
				this->weapon.getSprite()->setRotation(0);
			}
			else if (this->getCurrentKeyFrameX() == 1)
				this->weapon.getSprite()->setPosition(this->getSprite()->getPosition().x - 4 * fullscreenMultiplier, this->getSprite()->getPosition().y - 15 * fullscreenMultiplier);
			else if (this->getCurrentKeyFrameX() == 2)
				this->weapon.getSprite()->setPosition(this->getSprite()->getPosition().x - 12 * fullscreenMultiplier, this->getSprite()->getPosition().y - 11 * fullscreenMultiplier);
			else if (this->getCurrentKeyFrameX() == 3)
			{
				this->weapon.getSprite()->setPosition(this->getSprite()->getPosition().x + 2 * fullscreenMultiplier, this->getSprite()->getPosition().y + 5 * fullscreenMultiplier);
				this->weapon.getSprite()->setRotation(90);
			}
		}
	}
	else
	{
		this->setCurrentKeyFrameX(3);
		this->weapon.getSprite()->setPosition(-500, -500);
		this->weapon.setCurrentKeyFrameX(3);
		if (this->getCurrentKeyFrameY() == 4)
		{
			this->setCurrentKeyFrameY(0);
		}
		else if (this->getCurrentKeyFrameY() == 5)
		{
			this->setCurrentKeyFrameY(1);
		}
		else if (this->getCurrentKeyFrameY() == 6)
		{
			this->setCurrentKeyFrameY(2);
		}
		else if (this->getCurrentKeyFrameY() == 7)
		{
			this->setCurrentKeyFrameY(3);
		}
	}
	

	wasWpressed = isWpressed;
	wasApressed = isApressed;
	wasSpressed = isSpressed;
	wasDpressed = isDpressed;
	wasSpacePressed = isSpacePressed;

	if (this->getSprite()->getPosition().x > 192 * fullscreenMultiplier)
		this->getSprite()->setPosition(-16 * fullscreenMultiplier, this->getSprite()->getPosition().y);
	else if (this->getSprite()->getPosition().x < -16 * fullscreenMultiplier)
		this->getSprite()->setPosition(192 * fullscreenMultiplier, this->getSprite()->getPosition().y);
	else if (this->getSprite()->getPosition().y > 108 * fullscreenMultiplier)
		this->getSprite()->setPosition(this->getSprite()->getPosition().x, -16 * fullscreenMultiplier);
	else if (this->getSprite()->getPosition().y < -16 * fullscreenMultiplier)
		this->getSprite()->setPosition(this->getSprite()->getPosition().x, 108 * fullscreenMultiplier);
}

void Player::collision(float dt, bool isFullscreen, int collisionType)
{
	if (isFullscreen && !wasFullscreen)
	{
		this->speed *= 10.f;
	}
	else if (!isFullscreen && wasFullscreen)
	{
		this->speed *= 0.1f;
	}

	wasFullscreen = isFullscreen;

	bool isWpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool isApressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool isSpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool isDpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	if (isDpressed && !isWpressed && !isSpressed && !isApressed)
		this->getSprite()->move(-speed*dt, 0);

	else if (isSpressed && !isApressed && !isDpressed && !isWpressed)
		this->getSprite()->move(0, -speed*dt);

	else if (isApressed && !isWpressed && !isSpressed && !isDpressed)
		this->getSprite()->move(speed*dt, 0);

	else if (isWpressed && !isApressed && !isDpressed && !isSpressed)
		this->getSprite()->move(0, speed*dt);

	else if (isSpressed && isDpressed)
		this->getSprite()->move(-sqrt(pow(speed, 2) / 2)*dt, -sqrt(pow(speed, 2) / 2)*dt);

	else if (isWpressed && isApressed)
		this->getSprite()->move(sqrt(pow(speed, 2) / 2)*dt, sqrt(pow(speed, 2) / 2)*dt);

	else if (isWpressed && isDpressed)
		this->getSprite()->move(-sqrt(pow(speed, 2) / 2)*dt, sqrt(pow(speed, 2) / 2)*dt);

	else if (isSpressed && isApressed)
		this->getSprite()->move(sqrt(pow(speed, 2) / 2)*dt, -sqrt(pow(speed, 2) / 2)*dt);
}

Object * Player::drawWeapon()
{
	return &this->weapon;
}

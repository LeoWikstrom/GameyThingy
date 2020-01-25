#include "Enemy.h"



Enemy::Enemy()
{
}

Enemy::Enemy(float speed, int health, int damage, int value, sf::Vector2i keyFrameSize, sf::Vector2i spriteSheetSize, sf::Vector2i currentKeyFrame, sf::Vector2f startPosition, float animationSpeed, float keyFrameDuration, std::string fileName) : Obstacle(health, damage, value, keyFrameSize,
	spriteSheetSize,
	currentKeyFrame,
	startPosition,
	animationSpeed,
	keyFrameDuration,
	fileName)
{
	this->speed = speed;
	this->startHealth = health;
	srand(time(NULL));
}


Enemy::~Enemy()
{
}

void Enemy::reset(bool isFullscreen)
{
	this->setHealth(this->startHealth);
	Object::reset(isFullscreen);
}

void Enemy::detectPlayer(int posDifX, int posDifY)
{
	if (!isCollision)
	{
		if (posDifX > 0 && posDifY > 0)
		{
			if (posDifX > posDifY)
			{
				this->directionX = -1;
				this->directionY = 0;
			}
			else if (posDifX < posDifY)
			{
				this->directionY = -1;
				this->directionX = 0;
			}
		}
		else if (posDifX < 0 && posDifY < 0)
		{
			if (posDifX < posDifY)
			{
				this->directionX = 1;
				this->directionY = 0;
			}
			else if (posDifX > posDifY)
			{
				this->directionY = 1;
				this->directionX = 0;
			}
		}
		else if (posDifX < 0 && posDifY > 0)
		{
			if (posDifX * -1 > posDifY)
			{
				this->directionX = 1;
				this->directionY = 0;
			}
			else if (posDifX * -1 < posDifY)
			{
				this->directionY = -1;
				this->directionX = 0;
			}
		}
		else if (posDifX > 0 && posDifY < 0)
		{
			if (posDifX > posDifY * -1)
			{
				this->directionX = -1;
				this->directionY = 0;
			}
			else if (posDifX < posDifY * -1)
			{
				this->directionY = 1;
				this->directionX = 0;
			}
		}
	}

	isCollision = false;
	playerDetected = true;
}

void Enemy::collision(float dt, bool isFullscreen, int collisionType)
{
	isCollision = true;
	if (isFullscreen && !wasFullscreen)
	{
		this->speed *= 10.f;
	}
	else if (!isFullscreen && wasFullscreen)
	{
		this->speed *= 0.1f;
	}

	wasFullscreen = isFullscreen;

	if (this->directionX == 1)
	{
		this->getSprite()->move(-speed * collisionType*dt, 0);
		this->directionX = 0;
	}
	else if (this->directionY == 1)
		this->getSprite()->move(0, -speed * collisionType *dt);

	else if (this->directionX == -1)
		this->getSprite()->move(speed * collisionType*dt, 0);

	else if (this->directionY == -1)
		this->getSprite()->move(0, speed * collisionType *dt);

	this->directionX *= -1;
	this->directionY *= -1;

	if (collisionType == 800 && this->hurtTimer.getElapsedTime().asSeconds() > .1f)
	{
		this->setHealth(this->getHealth() - 1);
		this->getSprite()->setColor(sf::Color::Red);
		this->hurtTimer.restart();
	}
	if (this->getHealth() == 0)
	{
		this->setCurrentKeyFrameY(4);
		isKilled = true;
	}
}

void Enemy::Update(float dt, bool isFullscreen)
{
	if (isFullscreen)
	{
		if (!wasFullscreen)
		{
			this->speed *= 10.f;
		}
	}
	if (!isFullscreen)
	{
		if (wasFullscreen)
		{
			this->speed *= 0.1f;
		}
	}

	wasFullscreen = isFullscreen;

	if (this->hurtTimer.getElapsedTime().asSeconds() > .1f)
		this->getSprite()->setColor(sf::Color::White);

	if (this->moveTimer.getElapsedTime().asSeconds() > 2.f && !(this->playerDetected))
	{
		directionX = rand() % 3 - 1;
		directionY = rand() % 3 - 1;
		this->moveTimer.restart();
	}

	this->playerDetected = false;
	if (!isKilled)
	{
		if (directionX != 0)
		{
			this->getSprite()->move(speed*dt*directionX, 0);
			directionY = 0;
		}
		else
			this->getSprite()->move(0, speed*dt*directionY);


		if (directionX == 0 && directionY == 0)
		{
			this->setCurrentKeyFrameX(4);
		}
		else if (directionX == 1) //Move right
		{
			this->setCurrentKeyFrameY(2);
		}
		else if (directionY == 1) //Move down
		{
			this->setCurrentKeyFrameY(0);
		}
		else if (directionX == -1) // Move left
		{
			this->setCurrentKeyFrameY(3);
		}
		else if (directionY == -1) //Move up
		{
			this->setCurrentKeyFrameY(1);
		}
	}
	this->Object::Update(dt, isFullscreen);

	if (hurtTimer.getElapsedTime().asSeconds() > 0.5f && isKilled)
	{
		this->reset(isFullscreen);
		isKilled = false;
	}

	if (!isFullscreen)
	{
		if (this->getSprite()->getPosition().x > 192)
			this->getSprite()->setPosition(-16, this->getSprite()->getPosition().y);
		else if (this->getSprite()->getPosition().x < -16)
			this->getSprite()->setPosition(192, this->getSprite()->getPosition().y);
		else if (this->getSprite()->getPosition().y > 108)
			this->getSprite()->setPosition(this->getSprite()->getPosition().x, -16);
		else if (this->getSprite()->getPosition().y < -16)
			this->getSprite()->setPosition(this->getSprite()->getPosition().x, 108);
	}
	else
	{
		if (this->getSprite()->getPosition().x > 1920)
			this->getSprite()->setPosition(-160, this->getSprite()->getPosition().y);
		else if (this->getSprite()->getPosition().x < -160)
			this->getSprite()->setPosition(1920, this->getSprite()->getPosition().y);
		else if (this->getSprite()->getPosition().y > 1080)
			this->getSprite()->setPosition(this->getSprite()->getPosition().x, -160);
		else if (this->getSprite()->getPosition().y < -160)
			this->getSprite()->setPosition(this->getSprite()->getPosition().x, 1080);
	}

}

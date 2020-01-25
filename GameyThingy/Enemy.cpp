#include "Enemy.h"



Enemy::Enemy()
{
}

Enemy::Enemy(float speed, int view, int health, int damage, int value, sf::Vector2i keyFrameSize, sf::Vector2i spriteSheetSize, sf::Vector2i currentKeyFrame, sf::Vector2f startPosition, float animationSpeed, float keyFrameDuration, std::string fileName) : Obstacle(health, damage, value, keyFrameSize,
	spriteSheetSize,
	currentKeyFrame,
	startPosition,
	animationSpeed,
	keyFrameDuration,
	fileName)
{
	this->speed = speed;
	this->view = view;

	srand(time(NULL));
}


Enemy::~Enemy()
{
}

void Enemy::collision(float dt, bool isFullscreen)
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

	if (this->directionX == 1)
		this->sprite.move(-speed*dt, 0);

	else if (this->directionY == 1)
		this->sprite.move(0, -speed*dt);

	else if (this->directionX == -1)
		this->sprite.move(speed*dt, 0);

	else if (this->directionY == -1)
		this->sprite.move(0, speed*dt);

	this->directionX *= -1;
	this->directionY *= -1;
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

	if (this->moveTimer.getElapsedTime().asSeconds() > 2.f)
	{
		directionX = rand() % 3 - 1;
		directionY = rand() % 3 - 1;
		this->moveTimer.restart();
	}

	if (directionX != 0)
	{
		this->sprite.move(speed*dt*directionX, 0);
		directionY = 0;
	}
	else
		this->sprite.move(0, speed*dt*directionY);

	if (directionX == 0 && directionY == 0)
	{
		this->currentKeyFrame.x = 4;
	}
	else if (directionX == 1) //Move right
	{
		this->currentKeyFrame.y = 2;
	}
	else if (directionY == 1) //Move down
	{
		this->currentKeyFrame.y = 0;
	}
	else if (directionX == -1) // Move left
	{
		this->currentKeyFrame.y = 3;
	}
	else if (directionY == -1) //Move up
	{
		this->currentKeyFrame.y = 1;
	}

	this->Object::Update(dt, isFullscreen);

	if (!isFullscreen)
	{
		if (this->sprite.getPosition().x > 192)
			this->sprite.setPosition(-16, this->sprite.getPosition().y);
		else if (this->sprite.getPosition().x < -16)
			this->sprite.setPosition(192, this->sprite.getPosition().y);
		else if (this->sprite.getPosition().y > 108)
			this->sprite.setPosition(this->sprite.getPosition().x, -16);
		else if (this->sprite.getPosition().y < -16)
			this->sprite.setPosition(this->sprite.getPosition().x, 108);
	}
	else
	{
		if (this->sprite.getPosition().x > 1920)
			this->sprite.setPosition(-160, this->sprite.getPosition().y);
		else if (this->sprite.getPosition().x < -160)
			this->sprite.setPosition(1920, this->sprite.getPosition().y);
		else if (this->sprite.getPosition().y > 1080)
			this->sprite.setPosition(this->sprite.getPosition().x, -160);
		else if (this->sprite.getPosition().y < -160)
			this->sprite.setPosition(this->sprite.getPosition().x, 1080);
	}

}

#include "Obstacle.h"



Obstacle::Obstacle()
{
}

Obstacle::Obstacle(int health, int damage, int value, sf::Vector2i keyFrameSize, sf::Vector2i spriteSheetSize, sf::Vector2i currentKeyFrame, sf::Vector2f startPosition, float animationSpeed, float keyFrameDuration, std::string fileName) : Object(keyFrameSize,
	spriteSheetSize,
	currentKeyFrame,
	startPosition,
	animationSpeed,
	keyFrameDuration,
	fileName)
{
	this->health = health;
	this->damage = damage;
	this->value = value;
}


Obstacle::~Obstacle()
{
}

int Obstacle::getHealth() const
{
	return this->health;
}

void Obstacle::setHealth(int health)
{
	this->health = health;
}

int Obstacle::getValue() const
{
	return this->value;
}

void Obstacle::Update(float dt, bool isFullscreen)
{
	this->Object::Update(dt, isFullscreen);
}

#include "Item.h"



Item::Item()
{
}

Item::Item(int duration, int value, sf::Vector2i keyFrameSize, sf::Vector2i spriteSheetSize, sf::Vector2i currentKeyFrame, sf::Vector2f startPosition, float animationSpeed, float keyFrameDuration, std::string fileName) : Object(keyFrameSize,
	spriteSheetSize,
	currentKeyFrame,
	startPosition,
	animationSpeed,
	keyFrameDuration,
	fileName)
{
	this->duration = duration;
	this->value = value;
}

Item::~Item()
{
}

void Item::Update(float dt, bool isFullscreen)
{
}

void Item::collision(float dt, bool isFullscreen)
{
	std::cout << "Hello" << std::endl;
}

void Item::detectPlayer(int posDifX, int posDifY)
{
}

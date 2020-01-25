#include "Object.h"

void Object::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

Object::Object()
{
	this->keyFrameSize = sf::Vector2i(16, 16);
	this->spriteSheetSize = sf::Vector2i(4, 1);
	this->currentKeyFrame = sf::Vector2i(0, 0);
	this->startPosition = sf::Vector2f(0, 0);
	this->animationSpeed = 0.15f;
	this->keyFrameDuration = 0.f;

	if (!this->spriteTexture.loadFromFile("Images/MainChar.png"))
	{
		//Error!
	}
	this->sprite.setTexture(spriteTexture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, this->keyFrameSize.x, this->keyFrameSize.y));
	//this->sprite.setScale(sf::Vector2f(10, 10));
	this->sprite.setPosition(startPosition);
}

Object::Object(sf::Vector2i keyFrameSize, sf::Vector2i spriteSheetSize, sf::Vector2i currentKeyFrame, sf::Vector2f startPosition, float animationSpeed, float keyFrameDuration, std::string fileName)
{
	this->keyFrameSize = keyFrameSize;
	this->spriteSheetSize = spriteSheetSize;
	this->currentKeyFrame = currentKeyFrame;
	this->startPosition = startPosition;
	this->animationSpeed = animationSpeed;
	this->keyFrameDuration = keyFrameDuration;

	if (!this->spriteTexture.loadFromFile(fileName))
	{
		//Error!
	}
	this->sprite.setTexture(spriteTexture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, this->keyFrameSize.x, this->keyFrameSize.y));
	this->sprite.setPosition(startPosition);
}

Object::~Object()
{
}

sf::FloatRect Object::BoundingBox()
{
	return this->sprite.getGlobalBounds();
}

void Object::reset(bool isFullscreen)
{
	if(isFullscreen)
		this->sprite.setPosition(this->startPosition.x * 10, this->startPosition.y * 10);
	else
		this->sprite.setPosition(this->startPosition.x, this->startPosition.y);
	this->currentKeyFrame = sf::Vector2i(0, 0);
}


void Object::Update(float dt, bool isFullscreen)
{
	if (isFullscreen && !wasFullscreen)
	{
		this->sprite.setScale(10, 10);
		this->sprite.setPosition(this->sprite.getPosition().x * 10, this->sprite.getPosition().y * 10);
	}
	else if (!isFullscreen && wasFullscreen)
	{
		this->sprite.setScale(1, 1);
		this->sprite.setPosition(this->sprite.getPosition().x / 10, this->sprite.getPosition().y / 10);
	}

	wasFullscreen = isFullscreen;

	this->keyFrameDuration += dt;
	if (this->keyFrameDuration > this->animationSpeed)
	{
		this->currentKeyFrame.x += 1;
		if (this->currentKeyFrame.x >= this->spriteSheetSize.x)
		{
			this->currentKeyFrame.x = 0;
		}
		this->sprite.setTextureRect(sf::IntRect(this->currentKeyFrame.x * this->keyFrameSize.x, this->currentKeyFrame.y * this->keyFrameSize.y, this->keyFrameSize.x, this->keyFrameSize.y));

		this->keyFrameDuration = 0;
	}
}

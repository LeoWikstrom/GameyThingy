#include "Player.h"

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(playerSprite, states);
}

Player::Player()
{
	this->keyFrameSize.x = 16;
	this->keyFrameSize.y = 16;
	this->spriteSheetSize.x = 2;
	this->spriteSheetSize.y = 1;
	this->currentKeyFrame.x = 0;
	this->currentKeyFrame.y = 0;
	this->animationSpeed = 0.15f;
	this->keyFrameDuration = 0.f;
	this->speedX = 0;
	this->speedY = 0;

	if (!this->spriteTexture.loadFromFile("Images/WalkingDown.png"))
	{
		//Error!
	}
	this->playerSprite.setTexture(spriteTexture);
	this->playerSprite.setTextureRect(sf::IntRect(0, 0, this->keyFrameSize.x, this->keyFrameSize.y));
	this->playerSprite.setScale(sf::Vector2f(10, 10));
}

Player::~Player()
{
}

void Player::movePlayer()
{
	bool pressed = false;
	bool isWPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool isAPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool isSPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool isDPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	if (isWPressed && !isSPressed)
	{
		if (!wasWPressed || wasAPressed && !isAPressed || wasSPressed || wasDPressed && !isDPressed)
		{
			this->spriteSheetSize.x = 2;
			this->spriteSheetSize.y = 2;
			if (!this->spriteTexture.loadFromFile("Images/WalkingUp.png"))
			{
				//Error!
			}
			pressed = true;
		}
		if (speedX == 0)
		{
			this->speedY = -0.3;
		}
		else
		{
			this->speedY = -0.21;
		}
	}
	if (isAPressed && !isDPressed)
	{
		if (wasWPressed && !isWPressed || !wasAPressed || wasSPressed && !isSPressed || wasDPressed)
		{
			this->spriteSheetSize.x = 2;
			this->spriteSheetSize.y = 1;
			if (!this->spriteTexture.loadFromFile("Images/WalkingLeft.png"))
			{
				//Error!
			}
			pressed = true;
		}if (speedY == 0)
		{
			this->speedX = -0.3;
		}
		else
		{
			this->speedX = -0.21;
		}
	}
	if (isSPressed && !isWPressed)
	{
		if (wasWPressed || wasAPressed && !isAPressed || !wasSPressed || wasDPressed && !isDPressed)
		{
			this->spriteSheetSize.x = 2;
			this->spriteSheetSize.y = 2;
			if (!this->spriteTexture.loadFromFile("Images/WalkingDown.png"))
			{
				//Error!
			}
			pressed = true;
		}
		if (speedX == 0)
		{
			this->speedY = 0.3;
		}
		else
		{
			this->speedY = 0.21;
		}
	}
	if (isDPressed && !isAPressed)
	{
		if (wasWPressed && !isWPressed || wasAPressed || wasSPressed && !isSPressed || !wasDPressed)
		{
			this->spriteSheetSize.x = 2;
			this->spriteSheetSize.y = 1;
			if (!this->spriteTexture.loadFromFile("Images/WalkingRight.png"))
			{
				//Error!
			}
			pressed = true;
		}
		if (speedY == 0)
		{
			this->speedX = 0.3;
		}
		else
		{
			this->speedX = 0.21;
		}
	}
	if ( !isWPressed && !isAPressed && !isDPressed && !isSPressed)
	{
		this->spriteSheetSize.x = 1;
		this->spriteSheetSize.y = 1;
	}
	if (!isWPressed && !isSPressed)
	{
		this->speedY = 0;
	}
	if (!isAPressed && !isDPressed)
	{
		this->speedX = 0;
	}
	if (pressed)
	{
		this->playerSprite.setTexture(spriteTexture);
		this->playerSprite.setTextureRect(sf::IntRect(0, 0, this->keyFrameSize.x, this->keyFrameSize.y));
		this->playerSprite.setScale(sf::Vector2f(10, 10));
		this->currentKeyFrame.x = 0;
		this->currentKeyFrame.y = 0;
	}
	this->wasWPressed = isWPressed;
	this->wasAPressed = isAPressed;
	this->wasSPressed = isSPressed;
	this->wasDPressed = isDPressed;

	if (playerSprite.getPosition().x > 1920)
		playerSprite.setPosition(-160, playerSprite.getPosition().y);
	else if (playerSprite.getPosition().y > 640)
		playerSprite.setPosition(playerSprite.getPosition().x, -160);
	else if (playerSprite.getPosition().x < -160)
		playerSprite.setPosition(1920, playerSprite.getPosition().y);
	else if (playerSprite.getPosition().y < -160)
		playerSprite.setPosition(playerSprite.getPosition().x,  640);
}

void Player::Update(float dt)
{
	this->movePlayer();
	this->playerSprite.move(this->speedX, this->speedY);

	this->keyFrameDuration += dt;
	if (this->keyFrameDuration > this->animationSpeed)
	{
		this->currentKeyFrame.x += 1;
		if (this->currentKeyFrame.x >= this->spriteSheetSize.x)
		{
			this->currentKeyFrame.x = 0;
			this->currentKeyFrame.y += 1;
			if (this->currentKeyFrame.y >= this->spriteSheetSize.y)
			{
				this->currentKeyFrame.y = 0;
			}
		}
		this->playerSprite.setTextureRect(sf::IntRect(this->currentKeyFrame.x * this->keyFrameSize.x, this->currentKeyFrame.y * this->keyFrameSize.y, this->keyFrameSize.x, this->keyFrameSize.y));

		this->keyFrameDuration = 0;
	}
}

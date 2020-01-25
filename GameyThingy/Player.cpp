#include "Player.h"

Player::Player() : Object()
{
	this->speed = 50;
	this->health = 3;
	this->score = 0;
}

Player::Player(float speed, int health, int score, sf::Vector2i keyFrameSize, sf::Vector2i spriteSheetSize, sf::Vector2i currentKeyFrame, sf::Vector2f startPosition, float animationSpeed, float keyFrameDuration, std::string fileName) : Object(keyFrameSize,
	spriteSheetSize,
	currentKeyFrame,
	startPosition,
	animationSpeed,
	keyFrameDuration,
	fileName)
{
	this->speed = speed;
	this->health = health;
	this->score = score;
}

Player::~Player()
{
}

void Player::Update(float dt, bool isFullscreen)
{
	
	if (isFullscreen)
	{
		this->sprite.setScale(10, 10);
		this->speed = 500;
		if(!wasFullscreen)
			this->sprite.setPosition(this->sprite.getPosition().x * 10, this->sprite.getPosition().y * 10);
	}
	else
	{
		this->sprite.setScale(1, 1);
		this->speed = 50;
		if (wasFullscreen)
			this->sprite.setPosition(this->sprite.getPosition().x / 10, this->sprite.getPosition().y / 10);
	}

	wasFullscreen = isFullscreen;

	bool isWpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool isApressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool isSpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool isDpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	if (isWpressed && !isApressed && !isDpressed) //Move up
	{
		if (!wasWpressed)
			this->currentKeyFrame.x = 0;
		this->currentKeyFrame.y = 1;
		this->sprite.move(0, -speed*dt);
	}
	else if (isApressed && !isWpressed && !isSpressed) //Move left
	{
		if (!wasApressed)
			this->currentKeyFrame.x = 0;
		this->currentKeyFrame.y = 3;
		this->sprite.move(-speed*dt, 0);
	}
	else if (isSpressed && !isApressed && !isDpressed) //Move down
	{
		if (!wasSpressed)
			this->currentKeyFrame.x = 0;
		this->currentKeyFrame.y = 0;
		this->sprite.move(0, speed*dt);
	}
	else if (isDpressed && !isWpressed && !isSpressed) //Move right
	{
		if (!wasDpressed)
			this->currentKeyFrame.x = 0;
		this->currentKeyFrame.y = 2;
		this->sprite.move(speed*dt, 0);
	}
	else if (isWpressed && isApressed) //Move up-left
	{
		if (!wasWpressed && !wasApressed)
			this->currentKeyFrame.x = 0;
		if (!wasWpressed)
			this->currentKeyFrame.y = 3;
		if (!wasApressed)
			this->currentKeyFrame.y = 1;
		this->sprite.move(-sqrt(pow(speed, 2)/2)*dt, -sqrt(pow(speed, 2)/2)*dt);
	}
	else if (isWpressed && isDpressed) //Move up-right
	{
		if (!wasWpressed && !wasDpressed)
			this->currentKeyFrame.x = 0;
		if (!wasWpressed)
			this->currentKeyFrame.y = 2;
		if(!wasDpressed)
			this->currentKeyFrame.y = 1;
		this->sprite.move(sqrt(pow(speed, 2) / 2)*dt, -sqrt(pow(speed, 2) / 2)*dt);
	}
	else if (isSpressed && isApressed) //Move down-left
	{
		if (!wasSpressed && !wasApressed)
			this->currentKeyFrame.x = 0;
		if (!wasSpressed)
			this->currentKeyFrame.y = 3;
		if (!wasApressed)
			this->currentKeyFrame.y = 0;
		this->sprite.move(-sqrt(pow(speed, 2) / 2)*dt, sqrt(pow(speed, 2) / 2)*dt);
	}
	else if (isSpressed && isDpressed) //Move down-right
	{
		if (!wasSpressed && !wasDpressed)
			this->currentKeyFrame.x = 0;
		if (!wasSpressed)
			this->currentKeyFrame.y = 2;
		if (!wasDpressed)
			this->currentKeyFrame.y = 0;
		this->sprite.move(sqrt(pow(speed, 2) / 2)*dt, sqrt(pow(speed, 2) / 2)*dt);
	}
	else
	{
		this->currentKeyFrame.x = 4;
	}

	this->Object::Update(dt);

	wasWpressed = isWpressed;
	wasApressed = isApressed;
	wasSpressed = isSpressed;
	wasDpressed = isDpressed;

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

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
	if (isFullscreen && !wasFullscreen)
	{
		this->speed *= 10.f;
	}
	else if (!isFullscreen && wasFullscreen)
	{
		this->speed *= 0.1f;
	}

	this->Object::Update(dt, isFullscreen);


	wasFullscreen = isFullscreen;

	bool isWpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool isApressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool isSpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool isDpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	if (isWpressed && !isApressed && !isDpressed && !isSpressed) //Move up
	{
		if (!wasWpressed)
			this->currentKeyFrame.x = 0;
		this->currentKeyFrame.y = 1;
		this->sprite.move(0, -speed*dt);
	}
	else if (isApressed && !isWpressed && !isSpressed && !isDpressed) //Move left
	{
		if (!wasApressed)
			this->currentKeyFrame.x = 0;
		this->currentKeyFrame.y = 3;
		this->sprite.move(-speed*dt, 0);
	}
	else if (isSpressed && !isApressed && !isDpressed && !isWpressed) //Move down
	{
		if (!wasSpressed)
			this->currentKeyFrame.x = 0;
		this->currentKeyFrame.y = 0;
		this->sprite.move(0, speed*dt);
	}
	else if (isDpressed && !isWpressed && !isSpressed && !isApressed) //Move right
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
	else if (isApressed && isDpressed)
	{
		if (!wasApressed && !wasDpressed)
			this->currentKeyFrame.x = 0;
		if (!wasApressed)
			this->currentKeyFrame.y = 2;
		if (!wasDpressed)
			this->currentKeyFrame.y = 3;
	}
	else if (isWpressed && isSpressed)
	{
		if (!wasWpressed && !wasSpressed)
			this->currentKeyFrame.x = 0;
		if (!wasWpressed)
			this->currentKeyFrame.y = 0;
		if (!wasSpressed)
			this->currentKeyFrame.y = 1;
	}
	else
	{
		this->currentKeyFrame.x = 4;
	}

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

void Player::collision(float dt, bool isFullscreen)
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
		this->sprite.move(-speed*dt, 0);

	else if (isSpressed && !isApressed && !isDpressed && !isWpressed)
		this->sprite.move(0, -speed*dt);

	else if (isApressed && !isWpressed && !isSpressed && !isDpressed)
		this->sprite.move(speed*dt, 0);

	else if (isWpressed && !isApressed && !isDpressed && !isSpressed)
		this->sprite.move(0, speed*dt);

	else if (isSpressed && isDpressed)
		this->sprite.move(-sqrt(pow(speed, 2) / 2)*dt, -sqrt(pow(speed, 2) / 2)*dt);

	else if (isWpressed && isApressed)
		this->sprite.move(sqrt(pow(speed, 2) / 2)*dt, sqrt(pow(speed, 2) / 2)*dt);

	else if (isWpressed && isDpressed)
		this->sprite.move(-sqrt(pow(speed, 2) / 2)*dt, sqrt(pow(speed, 2) / 2)*dt);

	else if (isSpressed && isApressed)
		this->sprite.move(sqrt(pow(speed, 2) / 2)*dt, -sqrt(pow(speed, 2) / 2)*dt);
}

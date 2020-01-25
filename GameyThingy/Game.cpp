#include "Game.h"
#include <iostream>
Game::Game()
{
	if (!backgroundTexture.loadFromFile("Images/Background.png"))
	{
		//Error!
	}
	this->back.setTexture(backgroundTexture);
	this->back.setTextureRect(sf::IntRect(0, 0, 192, 108));

	if (!heartTexture.loadFromFile("Images/HeartSprite.png"))
	{
		//Error!
	}
	for (int n = 0; n < 3; n++)
	{
		this->hearts[n].setTexture(heartTexture);
		this->hearts[n].setTextureRect(sf::IntRect(0, 0, 8, 8));
		this->hearts[n].setPosition(sf::Vector2f(2 + 8 * (float)n, 1));
	}

	this->objects = new Object*[objectCapacity];
	this->objects[0] = new Player(50.f, 3, 0, sf::Vector2i(16, 16), sf::Vector2i(4, 1), sf::Vector2i(0, 0), sf::Vector2f(88, 46), 0.15f, 0.f, (std::string)"Images/MainChar.png");
	this->nrOfObjects++;

	if (!font.loadFromFile("Fonts/pkmn.ttf"))
	{
		//Error!
	}
	showScore.setFont(font);
	showScore.setCharacterSize(14);
	showScore.setFillColor(sf::Color::Black);
	showScore.setPosition(2, 92);

	pressSpace.setFont(font);
	pressSpace.setCharacterSize(30);
	pressSpace.setFillColor(sf::Color::White);
	pressSpace.setPosition(15, 34);
	pressSpace.setString("Press SPACE");

	this->createLevel(4, false);
}

Game::~Game()
{
	for (int n = 0; n < nrOfObjects; n++)
		delete this->objects[n];
	delete[] this->objects;
}

void Game::createLevel(int nrOfEnemies, bool isFullscreen)
{
	if (this->nrOfObjects < 15 && nrOfEnemies > 0)
	{
		int currentNrOfObjects = nrOfObjects;
		for (int n = currentNrOfObjects; n < currentNrOfObjects + nrOfEnemies / 2; n++)
		{
			this->objects[n] = new Enemy(40.f, 0, 3, 1, 50, sf::Vector2i(16, 16), sf::Vector2i(4, 1), sf::Vector2i(0, 0), sf::Vector2f(-500.f, 18.f * (float)n), 0.15f, 0.f, (std::string)"Images/RedKnight.png");
			this->nrOfObjects++;
		}
		for (int n = currentNrOfObjects + nrOfEnemies / 2; n < currentNrOfObjects + nrOfEnemies; n++)
		{
			this->objects[n] = new Enemy(30.f, 0, 1, 1, 50, sf::Vector2i(16, 16), sf::Vector2i(4, 1), sf::Vector2i(0, 0), sf::Vector2f(-500.f, 18.f * (float)n), 0.15f, 0.f, (std::string)"Images/BlueKnight.png");
			this->nrOfObjects++;
		}
		collisions = CollisionHandler(this->objects, this->nrOfObjects);
	}
	for (int n = 0; n < this->nrOfObjects; n++)
	{
		this->objects[n]->reset(isFullscreen);
	}
}

void Game::Update(float dt, bool isFullscreen)
{
	if (isFullscreen && !wasFullscreen)
	{
		this->back.setScale(sf::Vector2f(10, 10));
		this->showScore.setScale(sf::Vector2f(10, 10));
		this->showScore.setPosition(20, 920);
		this->pressSpace.setScale(sf::Vector2f(10, 10));
		this->pressSpace.setPosition(150, 340);
		for (int n = 0; n < 3; n++)
		{
			this->hearts[n].setScale(sf::Vector2f(10, 10));
			this->hearts[n].setPosition(this->hearts[n].getPosition().x * 10, this->hearts[n].getPosition().y * 10);
		}
		for (int n = 0; n < nrOfObjects; n++)
		{
			this->objects[n]->Update(0, isFullscreen);
		}
	}
	else if (!isFullscreen && wasFullscreen)
	{
		this->back.setScale(sf::Vector2f(1, 1));
		this->showScore.setScale(sf::Vector2f(1, 1));
		this->showScore.setPosition(2, 92);
		this->pressSpace.setScale(sf::Vector2f(1, 1));
		this->pressSpace.setPosition(15, 34);
		for (int n = 0; n < 3; n++)
		{
			this->hearts[n].setScale(sf::Vector2f(1, 1));
			this->hearts[n].setPosition(this->hearts[n].getPosition().x / 10, this->hearts[n].getPosition().y / 10);
		}
		for (int n = 0; n < nrOfObjects; n++)
		{
			this->objects[n]->Update(0, isFullscreen);
		}
	}

	wasFullscreen = isFullscreen;

	if (isPaused && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		score = 0;
		scoreTimer.restart();
		isPaused = false;
	}

	if (!isPaused)
	{
		for (int n = 0; n < nrOfObjects; n++)
		{
			this->objects[n]->Update(dt, isFullscreen);
		}

		nrOfCollisions = collisions.checkForCollision(collisionIndexes, isFullscreen);
		if (nrOfCollisions > 0)
		{
			for (int n = 0; n < nrOfCollisions; n++)
			{
				this->objects[collisionIndexes[n]]->collision(dt, isFullscreen);
				if (collisionIndexes[n] == 0 && hurtTimer.getElapsedTime().asSeconds() > 1.f)
				{
					nrOfHearts--;
					if (nrOfHearts <= 0)
					{
						nrOfHearts = 3;
						this->createLevel(0, isFullscreen);
						scoreTimer.restart();
						isPaused = true;
					}
					hurtTimer.restart();
				}
			}
		}
		if(!isPaused)
			score = (int)(scoreTimer.getElapsedTime().asMilliseconds() * 0.05);
		showScore.setString(std::to_string(score));
	}
}

void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(back);
	for (int n = 0; n < nrOfObjects; n++)
	{
		target.draw(*(this->objects[n]));
	}
	for (int n = 0; n < nrOfHearts; n++)
	{
		target.draw(hearts[n]);
	}
	target.draw(showScore);
	if (isPaused && (int)scoreTimer.getElapsedTime().asSeconds()%2 == 0)
		target.draw(pressSpace);
}

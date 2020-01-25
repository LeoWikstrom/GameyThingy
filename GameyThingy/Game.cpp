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
		this->hearts[n].setPosition(sf::Vector2f(2 + 8 * n, 1));
	}

	this->objects = new Object*[objectCapacity];
	this->objects[0] = new Player(50.f, 3, 0, sf::Vector2i(16, 16), sf::Vector2i(4, 1), sf::Vector2i(0, 0), sf::Vector2f(88, 46), 0.15f, 0.f, (std::string)"Images/MainChar.png");
	this->nrOfObjects++;

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
			this->objects[n] = new Enemy(40.f, 0, 3, 1, 50, sf::Vector2i(16, 16), sf::Vector2i(4, 1), sf::Vector2i(0, 0), sf::Vector2f(-500, 18 * n), 0.15f, 0.f, (std::string)"Images/RedKnight.png");
			this->nrOfObjects++;
		}
		for (int n = currentNrOfObjects + nrOfEnemies / 2; n < currentNrOfObjects + nrOfEnemies; n++)
		{
			this->objects[n] = new Enemy(30.f, 0, 1, 1, 50, sf::Vector2i(16, 16), sf::Vector2i(4, 1), sf::Vector2i(0, 0), sf::Vector2f(-500, 18 * n), 0.15f, 0.f, (std::string)"Images/BlueKnight.png");
			this->nrOfObjects++;
		}
		collisions = CollisionHandler(this->objects, this->nrOfObjects);
	}
	std::cout << nrOfObjects << std::endl;
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
		for (int n = 0; n < 3; n++)
		{
			this->hearts[n].setScale(sf::Vector2f(10, 10));
			this->hearts[n].setPosition(this->hearts[n].getPosition().x * 10, this->hearts[n].getPosition().y * 10);
		}
	}
	else if(!isFullscreen && wasFullscreen)
	{
		this->back.setScale(sf::Vector2f(1, 1));
		for (int n = 0; n < 3; n++)
		{
			this->hearts[n].setScale(sf::Vector2f(1, 1));
			this->hearts[n].setPosition(this->hearts[n].getPosition().x / 10, this->hearts[n].getPosition().y / 10);
		}
	}

	wasFullscreen = isFullscreen;

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
				//std::cout << nrOfHearts << " - ";
				nrOfHearts--;
				if (nrOfHearts <= 0)
				{
					nrOfHearts = 3;
					this->createLevel(0, isFullscreen);
				}
				//std::cout << nrOfHearts << std::endl;
				hurtTimer.restart();
			}
		}
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
}

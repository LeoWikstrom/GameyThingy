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

	this->objects = new Object*[nrOfObjects];
	this->objects[0] = new Player(50.f, 3, 0, sf::Vector2i(16, 16), sf::Vector2i(4, 1), sf::Vector2i(0, 0), sf::Vector2f(10, 30), 0.15f, 0.f, (std::string)"Images/MainChar.png");

	this->createLevel();
}

Game::~Game()
{
	for (int n = 0; n < nrOfObjects; n++)
		delete this->objects[n];
	delete[] this->objects;
}

void Game::createLevel()
{
	for (int n = 1; n < 1 + nrOfEnemies/2; n++)
	{
		this->objects[n] = new Enemy(40.f, 0, 3, 1, 50, sf::Vector2i(16, 16), sf::Vector2i(4, 1), sf::Vector2i(0, 0), sf::Vector2f(50, 18 * n), 0.15f, 0.f, (std::string)"Images/RedKnight.png");
	}
	for (int n = 1 + nrOfEnemies/2; n < 1 + nrOfEnemies; n++)
	{
		this->objects[n] = new Enemy(30.f, 0, 1, 1, 50, sf::Vector2i(16, 16), sf::Vector2i(4, 1), sf::Vector2i(0, 0), sf::Vector2f(50, 18 * n), 0.15f, 0.f, (std::string)"Images/BlueKnight.png");
	}
	collisions = CollisionHandler(this->objects, this->nrOfObjects);
}

void Game::Update(float dt, bool isFullscreen)
{
	if(isFullscreen)
		this->back.setScale(sf::Vector2f(10, 10));
	else
		this->back.setScale(sf::Vector2f(1, 1));
	for (int n = 0; n < nrOfObjects; n++)
	{
		this->objects[n]->Update(dt, isFullscreen);
	}
	if (collisions.checkForCollision() != sf::Vector2i(-1, -1))
	{
		if (collisions.checkForCollision().x == 0)
		{
			Player * playerCollide = dynamic_cast<Player*>(this->objects[collisions.checkForCollision().x]);
			if (playerCollide != nullptr)
			{
				playerCollide->collision();
			}
		}
		else
		{
			Enemy * enemyCollide = dynamic_cast<Enemy*>(this->objects[collisions.checkForCollision().x]);
			if (enemyCollide != nullptr)
			{
				enemyCollide->collision();
			}
			enemyCollide = dynamic_cast<Enemy*>(this->objects[collisions.checkForCollision().y]);
			if (enemyCollide != nullptr)
			{
				enemyCollide->collision();
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
}

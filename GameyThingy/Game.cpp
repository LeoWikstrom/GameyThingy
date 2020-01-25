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
	//this->back.setScale(sf::Vector2f(10, 10));
}

Game::~Game()
{
}

void Game::Update(float dt, bool isFullscreen)
{
	if(isFullscreen)
		this->back.setScale(sf::Vector2f(10, 10));
	else
		this->back.setScale(sf::Vector2f(1, 1));
	player.Update(dt, isFullscreen);
	//player2.Update(dt);
}

void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(back);
	target.draw(player);
	//target.draw(player2);
}

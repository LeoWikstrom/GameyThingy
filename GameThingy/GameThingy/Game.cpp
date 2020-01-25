#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Update(float dt)
{
	player.Update(dt);
}

void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::Sprite back;
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("Images/Background.png"))
	{
		//Error!
	}
	back.setTexture(backgroundTexture);
	back.setTextureRect(sf::IntRect(0, 0, 192, 64));
	back.setScale(sf::Vector2f(10, 10));
	target.draw(back);
	target.draw(player);
}

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

	if (!menuTexture.loadFromFile("Images/Menu.png"))
	{
		//Error!
	}
	this->menu.setTexture(menuTexture);
	this->menu.setTextureRect(sf::IntRect(0, 0, 192, 108));

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
	this->objects[0] = new Player(50.f, 3, sf::Vector2i(16, 16), sf::Vector2i(4, 1), sf::Vector2i(0, 0), sf::Vector2f(88, 46), 0.15f, 0.f, (std::string)"Images/MainChar.png");
	this->nrOfObjects++;

	if (!font.loadFromFile("Fonts/pkmn.ttf"))
	{
		//Error!
	}
	showScore.setFont(font);
	showScore.setCharacterSize(14);
	showScore.setFillColor(sf::Color::White);
	showScore.setPosition(2, 92);

	pressEnter.setFont(font);
	pressEnter.setCharacterSize(30);
	pressEnter.setFillColor(sf::Color::White);
	pressEnter.setPosition(20, 34);
	pressEnter.setString("Press ENTER");

	play.setFont(font);
	play.setCharacterSize(20);
	play.setFillColor(sf::Color::White);
	play.setPosition(35, 57);
	play.setString("PLAY");

	highScore.setFont(font);
	highScore.setCharacterSize(20);
	highScore.setFillColor(sf::Color::White);
	highScore.setPosition(95, 57);
	highScore.setString("HIGHSCORE");

	escape.setFont(font);
	escape.setCharacterSize(10);
	escape.setFillColor(sf::Color::White);
	escape.setPosition(120, 92);
	escape.setString("Press ESC to exit");
	
	this->highscore.setFont(font);

	this->createLevel(4, false);

	this->menuPosition = sf::Vector2f(19, 61);
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
			this->objects[n] = new Enemy(40.f, 3, 1, 1000,sf::Vector2i(16, 16), sf::Vector2i(4, 1), sf::Vector2i(0, 0), sf::Vector2f(-500.f, 18.f * (float)n), 0.15f, 0.f, (std::string)"Images/RedKnight.png");
			this->nrOfObjects++;
		}
		for (int n = currentNrOfObjects + nrOfEnemies / 2; n < currentNrOfObjects + nrOfEnemies; n++)
		{
			this->objects[n] = new Enemy(30.f, 1, 1, 500, sf::Vector2i(16, 16), sf::Vector2i(4, 1), sf::Vector2i(0, 0), sf::Vector2f(-500.f, 18.f * (float)n), 0.15f, 0.f, (std::string)"Images/BlueKnight.png");
			this->nrOfObjects++;
		}
		collisions = CollisionHandler(this->objects, this->nrOfObjects);
	}
	if (nrOfEnemies == 0)
	{
		
		for (int n = 0; n < 5; n++)
		{
			this->objects[n]->reset(isFullscreen);
		}
		for (int n = 5; n < this->nrOfObjects; n++)
		{
			delete this->objects[n];
		}
		this->nrOfObjects = 5;
		collisions = CollisionHandler(this->objects, this->nrOfObjects);
	}
}

void Game::Update(float dt, bool isFullscreen)
{
	if (isFullscreen && !wasFullscreen)
	{
		this->back.setScale(sf::Vector2f(10, 10));
		this->menu.setScale(sf::Vector2f(10, 10));
		this->showScore.setCharacterSize(140);
		this->showScore.setPosition(20, 920);
		this->pressEnter.setCharacterSize(300);
		this->pressEnter.setPosition(200, 340);
		this->play.setCharacterSize(200);
		this->play.setPosition(350, 570);
		this->highScore.setCharacterSize(200);
		this->highScore.setPosition(950, 570);
		escape.setCharacterSize(100);
		escape.setPosition(1200, 920);
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
		this->menu.setScale(sf::Vector2f(1, 1));
		this->showScore.setCharacterSize(14);
		this->showScore.setPosition(2, 92);
		this->pressEnter.setCharacterSize(30);
		this->pressEnter.setPosition(20, 34);
		this->play.setCharacterSize(20);
		this->play.setPosition(35, 57);
		this->highScore.setCharacterSize(20);
		this->highScore.setPosition(95, 57);
		escape.setCharacterSize(10);
		escape.setPosition(120, 92);
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

	if (isInMenu)
	{
		int borderMod = 1;
		if (isFullscreen)
		{
			this->objects[0]->getSprite()->setPosition(menuPosition.x * 10, menuPosition.y * 10);
			borderMod = 10;
		}
		else
		{
			this->objects[0]->getSprite()->setPosition(menuPosition);
			borderMod = 1;
		}
		this->objects[0]->Update(dt, isFullscreen);

		Player*player = dynamic_cast<Player*>(objects[0]);
		if (player != nullptr)
			player->drawWeapon()->Update(dt, isFullscreen);

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && this->objects[0]->getSprite()->getPosition().x < 160 * borderMod)
		{
			this->menuPosition.x += 50 * dt;
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && this->objects[0]->getSprite()->getPosition().x > 16 * borderMod) {
			this->menuPosition.x -= 50 * dt;
		}

		if (this->objects[0]->getSprite()->getPosition().x < 75 * borderMod)
		{
			this->play.setFillColor(sf::Color::Red);
			this->highScore.setFillColor(sf::Color::White);
		}
		else 
		{
			this->play.setFillColor(sf::Color::White);
			this->highScore.setFillColor(sf::Color::Red);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && play.getFillColor() == sf::Color::Red && !showHighscore)
		{
			this->isInMenu = false;
			this->objects[0]->getSprite()->setPosition(this->objects[0]->getStartPosition().x * borderMod, this->objects[0]->getStartPosition().y * borderMod);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && highScore.getFillColor() == sf::Color::Red && !showHighscore)
		{
			showHighscore = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && showHighscore)
			showHighscore = false;
	}

	else
	{
		if (isPaused && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			score = 0;
			killPoints = 0;
			scoreTimer.restart();
			isPaused = false;
		}

		else if (isPaused && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			isInMenu = true;
		}

		else if (!isPaused)
		{
			for (int n = 0; n < nrOfObjects; n++)
			{
				this->objects[n]->Update(dt, isFullscreen);
			}
			Player*player = dynamic_cast<Player*>(objects[0]);
			if (player != nullptr)
				player->drawWeapon()->Update(dt, isFullscreen);
			if (collisions.checkForCollision(dt, isFullscreen, enemyValue) && hurtTimer.getElapsedTime().asSeconds() > 1.f)
			{
				nrOfHearts--;
				if (nrOfHearts <= 0)
				{
					nrOfHearts = 3;
					this->createLevel(0, isFullscreen);
					highscore.addScore(score);
					isPaused = true;
				}
				hurtTimer.restart();
			}
			if (enemyValue != 0)
				isEnemyDead = true;
			else
				isEnemyDead = false;
			if (isEnemyDead && !wasEnemyDead)
				killPoints += enemyValue;
			enemyValue = 0;
			wasEnemyDead = isEnemyDead;
			score = (int)(scoreTimer.getElapsedTime().asMilliseconds() * 0.05) + killPoints;

			if (scoreTimer.getElapsedTime().asMilliseconds() % 20000 == 0 && (int)scoreTimer.getElapsedTime().asMilliseconds() != 0)
				this->createLevel(2, isFullscreen);
			showScore.setString(std::to_string(score));
		}
	}
	highscore.update(isFullscreen);
}

void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (!isInMenu)
	{
		target.draw(back);
		for (int n = 1; n < nrOfObjects; n++)
		{
			target.draw(*(this->objects[n]));
		}
		Player*player = dynamic_cast<Player*>(objects[0]);
		if (player != nullptr)
		{
			if (hurtTimer.getElapsedTime().asSeconds() < 1.f && hurtTimer.getElapsedTime().asMilliseconds() % 200 == 0)
				player->getSprite()->setColor(sf::Color::Red);
			else if (hurtTimer.getElapsedTime().asSeconds() < 1.f && hurtTimer.getElapsedTime().asMilliseconds() % 200 == 100 || hurtTimer.getElapsedTime().asSeconds() > 1.f)
				player->getSprite()->setColor(sf::Color::White);
			target.draw(*(player->drawWeapon()));
			target.draw(*(player));
		}
		for (int n = 0; n < nrOfHearts; n++)
		{
			target.draw(hearts[n]);
		}
		target.draw(showScore);
		if (isPaused && (int)scoreTimer.getElapsedTime().asSeconds() % 2 == 0)
			target.draw(pressEnter);
		if (isPaused)
			target.draw(escape);
	}
	else if(isInMenu && !showHighscore)
	{
		target.draw(menu);
		target.draw(play);
		target.draw(highScore);
		Player*player = dynamic_cast<Player*>(objects[0]);
		if (player != nullptr)
		{
			target.draw(*(player->drawWeapon()));
			target.draw(*(player));
		}
	}

	else if (isInMenu && showHighscore)
	{
		target.draw(highscore);
		target.draw(escape);
	}
}

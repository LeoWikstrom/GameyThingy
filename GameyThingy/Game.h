#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "CollisionHandler.h"
#include "Highscore.h"

class Game : public sf::Drawable
{
private:
	Object** objects;
	int nrOfObjects = 0;
	int objectCapacity = 15;
	int nrOfHearts = 3;
	int score = 0;
	int killPoints = 0;
	int enemyValue = 0;
	CollisionHandler collisions;
	Highscore highscore;

	sf::Sprite back;
	sf::Texture backgroundTexture;
	sf::Sprite menu;
	sf::Texture menuTexture;
	sf::Sprite hearts[3];
	sf::Texture heartTexture;

	sf::Font font;
	sf::Text showScore;
	sf::Text pressEnter;
	sf::Text play;
	sf::Text highScore;
	sf::Text escape;

	std::string input;

	sf::Vector2f menuPosition;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool wasFullscreen = false;
	bool isPaused = true;
	bool isEnemyDead = false;
	bool wasEnemyDead = false;
	bool isInMenu = true;
	bool showHighscore = false;

	sf::Clock hurtTimer;
	sf::Clock scoreTimer;

public:
	Game();
	~Game();

	void createLevel(int nrOfEnemies, bool isFullscreen);

	void Update(float dt, bool isFullscreen);
};

#endif // !GAME_H
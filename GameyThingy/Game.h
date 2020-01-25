#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "CollisionHandler.h"

class Game : public sf::Drawable
{
private:
	Object** objects;
	int nrOfObjects = 9;
	int nrOfEnemies = 8;
	CollisionHandler collisions;

	sf::Sprite back;
	sf::Texture backgroundTexture;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	Game();
	~Game();

	void createLevel();

	void Update(float dt, bool isFullscreen);
};

#endif // !GAME_H
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
	int nrOfObjects = 0;
	int objectCapacity = 15;
	int collisionIndexes[15];
	int nrOfHearts = 3;
	int nrOfCollisions;
	CollisionHandler collisions;

	sf::Sprite back;
	sf::Texture backgroundTexture;
	sf::Sprite hearts[3];
	sf::Texture heartTexture;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool wasFullscreen = false;

	sf::Clock hurtTimer;

public:
	Game();
	~Game();

	void createLevel(int nrOfEnemies, bool isFullscreen);

	void Update(float dt, bool isFullscreen);
};

#endif // !GAME_H
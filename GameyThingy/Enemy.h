#ifndef ENEMY_H
#define ENEMY_H

#include "Obstacle.h"
#include <ctime>
#include <cstdlib>

class Enemy : public Obstacle
{
private:
	float speed;
	int startHealth;
	int directionX;
	int directionY;

	sf::Clock moveTimer;
	sf::Clock hurtTimer;

	bool wasFullscreen = false;
	bool playerDetected = false;
	bool isCollision = false;
	bool isKilled = false;

public:
	Enemy();
	Enemy(float speed, int health, int damage, int value,
		sf::Vector2i keyFrameSize,
		sf::Vector2i spriteSheetSize,
		sf::Vector2i currentKeyFrame,
		sf::Vector2f startPosition,
		float animationSpeed,
		float keyFrameDuration,
		std::string fileName);
	~Enemy();

	void reset(bool isFullscreen);
	void detectPlayer(int posDifX, int posDifY);
	void collision(float dt, bool isFullscreen, int collisionType);
	void Update(float dt, bool isFullscreen);
};


#endif // !ENEMY_H
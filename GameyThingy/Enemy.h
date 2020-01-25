#ifndef ENEMY_H
#define ENEMY_H

#include "Obstacle.h"
#include <ctime>
#include <cstdlib>

class Enemy : public Obstacle
{
private:
	float speed;
	int view;
	int directionX;
	int directionY;

	sf::Clock moveTimer;

	bool wasFullscreen = false;

public:
	Enemy();
	Enemy(float speed, int view, int health, int damage, int value,
		sf::Vector2i keyFrameSize,
		sf::Vector2i spriteSheetSize,
		sf::Vector2i currentKeyFrame,
		sf::Vector2f startPosition,
		float animationSpeed,
		float keyFrameDuration,
		std::string fileName);
	~Enemy();

	void collision(float dt, bool isFullscreen);
	void Update(float dt, bool isFullscreen);
};


#endif // !ENEMY_H
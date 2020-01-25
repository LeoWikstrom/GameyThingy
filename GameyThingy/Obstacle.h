#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Object.h"
class Obstacle : public Object
{
private:
	int damage;
	int health;
	int value;

public:
	Obstacle();
	Obstacle(int health, int damage, int value,
		sf::Vector2i keyFrameSize,
		sf::Vector2i spriteSheetSize,
		sf::Vector2i currentKeyFrame,
		sf::Vector2f startPosition,
		float animationSpeed,
		float keyFrameDuration,
		std::string fileName);
	~Obstacle();

	void Update(float dt, bool isFullscreen);
};


#endif // !OBSTACLE_H
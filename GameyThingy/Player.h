#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
class Player :	public Object
{
private:
	float speed;
	int health;
	int score;

	bool wasFullscreen = false;

	bool wasWpressed = false;
	bool wasApressed = false;
	bool wasSpressed = false;
	bool wasDpressed = false;

	sf::Clock runTime;
	//Weapon weapon

public:
	Player();
	Player(float speed, int health, int score,
		sf::Vector2i keyFrameSize,
		sf::Vector2i spriteSheetSize,
		sf::Vector2i currentKeyFrame,
		sf::Vector2f startPosition,
		float animationSpeed,
		float keyFrameDuration,
		std::string fileName);
	~Player();

	void Update(float dt, bool isFullscreen);
};


#endif // !PLAYER_H
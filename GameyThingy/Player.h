#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include "Weapon.h"

class Player :	public Object
{
private:
	float speed;
	int health;

	bool wasWpressed = false;
	bool wasApressed = false;
	bool wasSpressed = false;
	bool wasDpressed = false;
	bool wasSpacePressed = false;

	bool wasFullscreen = false;
	int fullscreenMultiplier;

	Weapon weapon =  Weapon(1, 3, 10, 100, sf::Vector2i(15, 22), sf::Vector2i(4, 1), sf::Vector2i(0, 0), sf::Vector2f(-15, -15), 0.15f, 0.f, (std::string)"Images/Sword.png");
public:
	Player();
	Player(float speed, int health,
		sf::Vector2i keyFrameSize,
		sf::Vector2i s,
		sf::Vector2i currentKeyFrame,
		sf::Vector2f startPosition,
		float animationSpeed,
		float keyFrameDuration,
		std::string fileName);
	~Player();

	void Update(float dt, bool isFullscreen);
	void collision(float dt, bool isFullscreen, int collisionType);

	Object* drawWeapon();
};


#endif // !PLAYER_H
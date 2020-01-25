#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
class Weapon : public Item
{
private:
	int damage;
	int nrOfUses;

public:
	Weapon();
	Weapon(int damage, int nrOfUses, int duration, int value,
		sf::Vector2i keyFrameSize,
		sf::Vector2i spriteSheetSize,
		sf::Vector2i currentKeyFrame,
		sf::Vector2f startPosition,
		float animationSpeed,
		float keyFrameDuration,
		std::string fileName);
	~Weapon();

	void Update(float dt, bool isFullscreen);
	void collision(float dt, bool isFullscreen, int collisionType);
	void detectPlayer(int posDifX, int posDifY);
};


#endif // !WEAPON_H
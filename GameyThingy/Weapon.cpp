#include "Weapon.h"

Weapon::Weapon()
{
}

Weapon::Weapon(int damage, int nrOfUses, int duration, int value, sf::Vector2i keyFrameSize, sf::Vector2i spriteSheetSize, sf::Vector2i currentKeyFrame, sf::Vector2f startPosition, float animationSpeed, float keyFrameDuration, std::string fileName) : Item(duration, value, keyFrameSize,
	spriteSheetSize,
	currentKeyFrame,
	startPosition,
	animationSpeed,
	keyFrameDuration,
	fileName)
{
	this->damage = damage;
	this->nrOfUses = nrOfUses;
}

Weapon::~Weapon()
{
}

void Weapon::Update(float dt, bool isFullscreen)
{
	Object::Update(dt, isFullscreen);
}

void Weapon::collision(float dt, bool isFullscreen, int collisionType)
{
	std::cout << "Hello" << std::endl;
}

void Weapon::detectPlayer(int posDifX, int posDifY)
{
}

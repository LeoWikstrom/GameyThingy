#ifndef ITEM_H
#define ITEM_H

#include "Object.h"
class Item : public Object
{
private:
	int duration;
	int value;
public:
	Item();
	Item(int duration, int value,
		sf::Vector2i keyFrameSize,
		sf::Vector2i spriteSheetSize,
		sf::Vector2i currentKeyFrame,
		sf::Vector2f startPosition,
		float animationSpeed,
		float keyFrameDuration,
		std::string fileName);
	~Item();

	void Update(float dt, bool isFullscreen);
	void collision(float dt, bool isFullscreen);
	void detectPlayer(int posDifX, int posDifY);
};


#endif // !ITEM_H
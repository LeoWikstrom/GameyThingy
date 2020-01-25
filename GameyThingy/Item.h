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
	~Item();

	void Update(float dt, bool isFullscreen);
};


#endif // !ITEM_H
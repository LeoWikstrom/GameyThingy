#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "Item.h"
class Consumable : public Item
{
private: 
	int effect;
	int power;

public:
	Consumable();
	~Consumable();

	void Update(float dt, bool isFullscreen);
};

#endif // !CONSUMABLE_H
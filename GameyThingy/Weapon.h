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
	~Weapon();

	void Update(float dt, bool isFullscreen);
};


#endif // !WEAPON_H
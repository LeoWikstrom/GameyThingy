#ifndef COLL_H
#define COLL_H

#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Player.h"
#include "Enemy.h"

class CollisionHandler
{
private:
	Object** objects;
	int nrOfObjects;

public:
	CollisionHandler();
	CollisionHandler(Object** objects, int nrOfObjects);
	~CollisionHandler();

	bool checkForCollision(float dt, bool isFullscreen, int & enemyValue) const;
};

#endif // !COLL_H
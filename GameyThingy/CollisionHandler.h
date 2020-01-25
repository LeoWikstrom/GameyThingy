#ifndef COLL_H
#define COLL_H

#include <SFML/Graphics.hpp>
#include "Object.h"

class CollisionHandler
{
private:
	Object** objects;
	int nrOfObjects;

public:
	CollisionHandler();
	CollisionHandler(Object** objects, int nrOfObjects);
	~CollisionHandler();

	int checkForCollision(int collisionIndexes[], bool isFullscreen) const;
};

#endif // !COLL_H
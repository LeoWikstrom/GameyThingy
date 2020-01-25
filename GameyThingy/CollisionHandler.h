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

	sf::Vector2i checkForCollision();
};

#endif // !COLL_H
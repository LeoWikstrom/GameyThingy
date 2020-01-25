#include "CollisionHandler.h"



CollisionHandler::CollisionHandler()
{
}

CollisionHandler::CollisionHandler(Object ** objects, int nrOfObjects)
{
	this->objects = objects;
	this->nrOfObjects = nrOfObjects;
}


CollisionHandler::~CollisionHandler()
{
}

sf::Vector2i CollisionHandler::checkForCollision()
{
	sf::Vector2i collisionIndex(-1, -1);

	for (int i = 0; i < nrOfObjects; i++)
	{
		for (int n = 1; n < nrOfObjects; n++)
		{
			if (i != n)
			{
				if (objects[i]->BoundingBox().intersects(objects[n]->BoundingBox()))
				{
					collisionIndex.x = i;
					collisionIndex.y = n;
				}
			}
		}
	}

	return collisionIndex;
}

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

int CollisionHandler::checkForCollision(int collisionIndexes[], bool isFullscreen) const
{
	int collisionIndent = 2;
	if (isFullscreen)
		collisionIndent = 20;

	sf::IntRect collisionRectI, collisionRectN;
	int pos = 0, nrOfCollisions = 0;
	for (int i = 0; i < nrOfObjects; i++)
	{
		collisionRectI = sf::IntRect(objects[i]->BoundingBox().left + collisionIndent, objects[i]->BoundingBox().top + collisionIndent, objects[i]->BoundingBox().width - collisionIndent, objects[i]->BoundingBox().height - collisionIndent);
 		for (int n = 0; n < nrOfObjects; n++)
		{
			if (i != n)
			{
				collisionRectN = sf::IntRect(objects[n]->BoundingBox().left + collisionIndent, objects[n]->BoundingBox().top + collisionIndent, objects[n]->BoundingBox().width - collisionIndent, objects[n]->BoundingBox().height - collisionIndent);
				if (collisionRectI.intersects(collisionRectN))
				{
					collisionIndexes[pos++] = i;
					nrOfCollisions += 1;
				}
			}
		}
	}
	return nrOfCollisions;
}
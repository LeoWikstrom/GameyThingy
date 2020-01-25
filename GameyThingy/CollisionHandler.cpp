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

bool CollisionHandler::checkForCollision(float dt, bool isFullscreen, int & enemyValue) const
{
	bool isPlayerColliding = false;

	int collisionIndent = 2;
	if (isFullscreen)
		collisionIndent = 20;

	sf::IntRect collisionRectI, collisionRectN, viewBox;
	Player*player = dynamic_cast<Player*>(objects[0]);
	sf::IntRect collisionRectSword(player->drawWeapon()->BoundingBox().left, player->drawWeapon()->BoundingBox().top , player->drawWeapon()->BoundingBox().width , player->drawWeapon()->BoundingBox().height );
	for (int i = 0; i < nrOfObjects; i++)
	{
		collisionRectI = sf::IntRect(objects[i]->BoundingBox().left + collisionIndent, objects[i]->BoundingBox().top + collisionIndent, objects[i]->BoundingBox().width - collisionIndent, objects[i]->BoundingBox().height - collisionIndent);
		if (i != 0 && collisionRectI.intersects(collisionRectSword) && player->drawWeapon()->getCurrentKeyFrameX() == 2 && objects[i]->getCurrentKeyFrameY() != 4)
		{
			this->objects[i]->collision(dt, isFullscreen, 800);
		}
		Enemy*enemy= dynamic_cast<Enemy*>(objects[i]);
		if (enemy != nullptr)
		{
			if (enemy->getHealth() == 0)
			{
				enemyValue += enemy->getValue();
			}
		}
		for (int n = 0; n < nrOfObjects; n++)
		{
			if (i != n)
			{
				collisionRectN = sf::IntRect(objects[n]->BoundingBox().left + collisionIndent, objects[n]->BoundingBox().top + collisionIndent, objects[n]->BoundingBox().width - collisionIndent, objects[n]->BoundingBox().height - collisionIndent);
				if (collisionRectI.intersects(collisionRectN) && ((i != 0 && objects[i]->getCurrentKeyFrameY() != 4) || i == 0))
				{
					this->objects[i]->collision(dt, isFullscreen, 1);
					if (i == 0)
						isPlayerColliding = true;
				}
			}
		}
	}

	int enemyView = 50;
	if (isFullscreen)
		enemyView = 500;
	int posDifX, posDifY;

	for (int n = 1; n < nrOfObjects; n++)
	{
		viewBox = sf::IntRect(objects[n]->BoundingBox().left - enemyView, objects[n]->BoundingBox().top - enemyView, objects[n]->BoundingBox().width + 2*enemyView, objects[n]->BoundingBox().height + 2*enemyView);
		if (viewBox.intersects(sf::IntRect(objects[0]->BoundingBox())))
		{
			posDifX = objects[n]->BoundingBox().left - objects[0]->BoundingBox().left;
			posDifY = objects[n]->BoundingBox().top - objects[0]->BoundingBox().top;
			objects[n]->detectPlayer(posDifX, posDifY);
		}
	}

	return isPlayerColliding;
}
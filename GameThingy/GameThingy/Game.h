#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"

class Game : public sf::Drawable
{
public:
	Game();
	~Game();

	void Update(float dt);

private:
	Player player;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // !GAME_H


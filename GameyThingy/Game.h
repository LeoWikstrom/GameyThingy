#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"

class Game : public sf::Drawable
{
private:
	Player player;
	//Player player2 = Player(0, 3, 0, sf::Vector2i(16, 16), sf::Vector2i(2, 2), sf::Vector2i(0, 0), sf::Vector2f(500, 300), 0.15f, 0.f, (std::string)"Images/WalkingDownRed.png");
	
	sf::Sprite back;
	sf::Texture backgroundTexture;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	Game();
	~Game();

	void Update(float dt, bool isFullscreen);


};

#endif // !GAME_H
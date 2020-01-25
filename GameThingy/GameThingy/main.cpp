#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	Game game;
	sf::RenderWindow window(sf::VideoMode(1920, 640), "Game Window");
	sf::Clock gameTime;
	window.setKeyRepeatEnabled(false);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		game.Update(gameTime.restart().asSeconds());
		window.clear();
		window.draw(game);
		window.display();
	}

	return 0;
}
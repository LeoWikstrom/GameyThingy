#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	Game game;
	sf::RenderWindow window(sf::VideoMode(192, 108), "Game Window");
	bool isFullscreen = false;
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
		{
			if (!isFullscreen)
			{
				window.create(sf::VideoMode(1920, 1080), "Game Window", sf::Style::Fullscreen);
				isFullscreen = true;
			}
			else
			{
				window.create(sf::VideoMode(192, 108), "Game Window");
				isFullscreen = false;
			}
		}
		game.Update(gameTime.restart().asSeconds(), isFullscreen);
		window.clear();
		window.draw(game);
		window.display();
	}

	return 0;
}
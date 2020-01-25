#include <SFML/Graphics.hpp>
#include "Game.h"
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	sf::RenderWindow window(sf::VideoMode(192, 108), "Game Window", sf::Style::Close);
	bool isFullscreen = false;
	sf::Clock gameTime;
	window.setKeyRepeatEnabled(false);
	float FPS;

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
				window.create(sf::VideoMode(192, 108), "Game Window", sf::Style::Close);
				isFullscreen = false;
			}
		}
		
		float dt = gameTime.restart().asSeconds();
		if (window.hasFocus())
		{
			FPS = 1 / dt;
			//std::cout << FPS << std::endl;
			game.Update(dt, isFullscreen);
			window.clear();
			window.draw(game);
			window.display();
		}
	}

	return 0;
}
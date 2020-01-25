#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Player : public sf::Drawable
{
private:
	sf::Texture spriteTexture;
	sf::Sprite playerSprite;
	sf::Vector2i keyFrameSize;
	sf::Vector2i spriteSheetSize;
	sf::Vector2i currentKeyFrame;
	float animationSpeed;
	float keyFrameDuration;
	bool wasWPressed = false;
	bool wasAPressed = false;
	bool wasSPressed = false;
	bool wasDPressed = false;
	float speedX;
	float speedY;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	Player();
	~Player();

	void movePlayer();
	void Update(float dt);

};

#endif // !PLAYER_H


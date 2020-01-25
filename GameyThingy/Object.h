#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Object : public sf::Drawable
{
protected:
	sf::Sprite sprite;
	sf::Vector2i currentKeyFrame;
private:
	sf::Texture spriteTexture;
	sf::Vector2i keyFrameSize;
	sf::Vector2i spriteSheetSize;
	sf::Vector2f startPosition;
	float animationSpeed;
	float keyFrameDuration;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	Object();
	Object(sf::Vector2i keyFrameSize,
	sf::Vector2i spriteSheetSize,
	sf::Vector2i currentKeyFrame,
	sf::Vector2f startPosition,
	float animationSpeed,
	float keyFrameDuration,
		std::string fileName);

	virtual ~Object();

	virtual void Update(float dt);

};

#endif // !OBJECT_H


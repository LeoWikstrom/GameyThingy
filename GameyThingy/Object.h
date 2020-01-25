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

	bool wasFullscreen = false;

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

	sf::FloatRect BoundingBox();

	virtual void Update(float dt, bool isFullscreen);

};

#endif // !OBJECT_H


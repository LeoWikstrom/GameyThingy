#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Object : public sf::Drawable
{
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
	void reset(bool isFullscreen);

	virtual void Update(float dt, bool isFullscreen);
	virtual void collision(float dt, bool isFullscreen) = 0;


	sf::Sprite sprite;
	sf::Vector2i currentKeyFrame;
};

#endif // !OBJECT_H


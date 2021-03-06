#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Object : public sf::Drawable
{
private:

	sf::Sprite sprite;
	sf::Vector2i currentKeyFrame;
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
	virtual void reset(bool isFullscreen);

	virtual void Update(float dt, bool isFullscreen);
	virtual void collision(float dt, bool isFullscreen, int collsionType) = 0;
	virtual void detectPlayer(int posDifX, int posDifY);
	
	void setCurrentKeyFrameX(int keyFrame);
	void setCurrentKeyFrameY(int keyFrame);
	int getCurrentKeyFrameX() const;
	int getCurrentKeyFrameY() const;
	sf::Vector2f getStartPosition() const;

	void setSprite(const sf::Sprite& sprite);
	sf::Sprite* getSprite();
};

#endif // !OBJECT_H


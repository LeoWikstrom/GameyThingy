#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

class Highscore : public sf::Drawable
{
private:
	int highScore[10];

	sf::Font font;
	sf::Text highScoreText[10];

	bool isHighscore = false;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Highscore();
	~Highscore();

	void addScore(int score);
	void setFont(sf::Font font);

	void update(bool isFullscreen);

};

#endif // !HIGHSCORE_H


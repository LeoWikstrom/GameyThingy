#include "Highscore.h"

void Highscore::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int n = 9; n >= 0; n--)
	{
		target.draw(highScoreText[n]);
	}
}

Highscore::Highscore()
{
	for (int n = 0; n < 10; n++)
	{
		this->highScore[n] = 0;

		highScoreText[n].setFont(font);
		highScoreText[n].setCharacterSize(100);
		highScoreText[n].setFillColor(sf::Color::White);
		highScoreText[n].setPosition(900, 100 * (9 - n) + 10);
		highScoreText[n].setString("0");
	}
}

Highscore::~Highscore()
{
}

void Highscore::addScore(int score)
{
	bool placeFound = false;
	for (int n = 0; n < 10 && !placeFound; n++)
	{
		if (score > this->highScore[n])
		{
			if (n != 0)
			{
				std::cout << n << std::endl;
				this->highScore[n - 1] = this->highScore[n];
				highScoreText[n - 1].setString(std::to_string(this->highScore[n - 1]));
				if (n == 9)
				{
					this->highScore[n] = score;
					isHighscore = true;
					highScoreText[n].setString(std::to_string(this->highScore[n]));
				}
			}
		}
		else if (score <= this->highScore[n])
		{
			if (n != 0)
			{
				this->highScore[n - 1] = score;
				isHighscore = true;
				highScoreText[n - 1].setString(std::to_string(this->highScore[n - 1]));
			}
			placeFound = true;
		}
	}
}

void Highscore::setFont(sf::Font font)
{
	this->font = font;
}

void Highscore::update(bool isFullscreen)
{
	if (isFullscreen)
	{
		for (int n = 9; n >= 0; n--)
		{
			highScoreText[n].setCharacterSize(100);
			highScoreText[n].setPosition(900, 100 * (9 - n) + 10);
		}
	}
	else
	{
		for (int n = 9; n >= 0; n--)
		{
			highScoreText[n].setCharacterSize(10);
			highScoreText[n].setPosition(90, 10 * (9 - n) + 1);
		}
	}
}

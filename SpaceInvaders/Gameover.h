#pragma once

#include "Globals.h"

#include <SFML/Graphics.hpp>
#include <iostream>

class Gameover
{
public:
	Gameover(sf::RenderWindow& _window);
	~Gameover() {};

	void draw();

private:
	sf::RenderWindow& window;

	sf::RectangleShape background;
	//sf::Texture texture;
	//sf::Sprite background;
	sf::Font mainTextFont;
	sf::Text mainText;

	sf::Font playTextFont;
	sf::Text playText;
	sf::Text quitText;
	bool playTextVisible = true;
	sf::Clock playTextClock;
	float textOnTime = 1.5;
	float textOffTime = 0.8;
};


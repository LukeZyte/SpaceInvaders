#pragma once

#include "Globals.h"

#include <SFML/Graphics.hpp>
#include <iostream>

class Level
{
public:
	Level(sf::RenderWindow& _window);
	~Level();

	void draw();
	void moveBackgorund(sf::Time& dt);

private:
	sf::RenderWindow& window;

	sf::IntRect irect{ 0, 0, 1200, 900 }; // left, top, width, height
	sf::Texture texture;
	sf::Sprite background;
	sf::Sprite background2;
	const int bgMaxSpeed = 400;
	int bgMoveSpeed = 0;
	const int acceleration = 1;

	const int transparency = 100;
};

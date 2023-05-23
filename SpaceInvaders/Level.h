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
	void moveBackgorund(sf::Time& dt, float gameSpeed = 1);
	void stopBackground();

private:
	sf::RenderWindow& window;

	sf::IntRect irect{ 0, 0, 1200, 900 }; // left, top, width, height
	sf::Texture texture;
	sf::Sprite background;
	sf::Sprite background2;
	const float bgMaxSpeed = 150;
	float bgMoveSpeed = 0;
	const float acceleration = 0.5;

	const int transparency = 100;
};

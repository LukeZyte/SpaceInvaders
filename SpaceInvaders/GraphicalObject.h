#pragma once

#include "Globals.h"

#include <iostream>
#include <SFML/Graphics.hpp>

class GraphicalObject
{
public:
	GraphicalObject(sf::RenderWindow* _window, std::string _texturePath, sf::Vector2f _initPosition);
	~GraphicalObject();

	virtual void resetPosition() = 0;
	virtual void draw() = 0;

protected:
	sf::RenderWindow* window;
	std::string texturePath;
	sf::Vector2f initPosition;

	sf::Texture texture;
	sf::Sprite sprite;
};


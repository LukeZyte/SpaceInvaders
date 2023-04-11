#pragma once

#include "Globals.h"

#include <iostream>
#include <SFML/Graphics.hpp>

class GraphicalObject
{
public:
	GraphicalObject(sf::RenderWindow* _window, std::string _texturePath, sf::Vector2f _initPosition);
	~GraphicalObject();

	void resetPosition();
	void draw();

protected:
	sf::RenderWindow* window;
	std::string texturePath;
	sf::Vector2f initPosition;

	sf::Texture texture;
	sf::Sprite sprite;
};


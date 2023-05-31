#pragma once

#include "GraphicalObject.h"

#include <SFML/Graphics.hpp>
#include <iostream>

class Wall :
    public GraphicalObject
{
public:
    Wall(sf::RenderWindow* _window, std::string _texturePath, sf::Vector2f _initPosition);
    ~Wall();

	bool collisionCheck(GraphicalObject* bullet);

	void hit();
	void changeTexture();
	void destroy();
	int getHP() { return HP; }

private:
	sf::Texture tex;
	int HP = 5;

};


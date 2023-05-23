#pragma once

#include "GraphicalObject.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Bullet : public GraphicalObject
{
public:
	Bullet(sf::RenderWindow* _window, std::string _texturePath, std::string _texturePath2, sf::Vector2f _initPosition);
	~Bullet();

	void moveEntity(sf::Time& dt, float gameSpeed = 1);

private:
	float bulletSpeed = 1000.f;
};


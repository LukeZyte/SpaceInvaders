#pragma once

#include "GraphicalObject.h"
#include "Bullet.h"
#include "Globals.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Player : public GraphicalObject
{
public:
	Player(sf::RenderWindow* _window, std::string _texturePath, sf::Vector2f _initPosition);//, std::vector<Bullet>& _bulletsVec);
	~Player();

	float getTopBound();
	sf::Vector2f getRifleBound();

	void movePlayer(sf::Time& dt, bool moveRight);
	void update(sf::Time& dt);

private:

	float moveSpeed = 250.f;
};



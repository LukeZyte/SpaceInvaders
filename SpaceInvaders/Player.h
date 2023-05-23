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
	Player(sf::RenderWindow* _window, std::string _texturePath, sf::Vector2f _initPosition);
	~Player();

	void resetPosition();
	void draw();
	void moveEntityLeft(sf::Time& dt, float gameSpeed = 1);
	void moveEntityRight(sf::Time& dt, float gameSpeed = 1);
	void moveEntity(sf::Time& dt, float gameSpeed = 1) {};
	sf::Vector2f getRifleBound();

	bool collisionCheck(GraphicalObject* bullet);
	void deathAnimation() {};
	void toggleTexture() {};

private:

	float moveSpeed = 500.f;
};

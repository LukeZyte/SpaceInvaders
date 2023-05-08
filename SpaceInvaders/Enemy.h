#pragma once

#include "GraphicalObject.h"
#include "Bullet.h"
#include "Globals.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Enemy : public GraphicalObject
{
public:
	Enemy(sf::RenderWindow* _window, std::string _texturePath, sf::Vector2f _initPosition);
	Enemy(sf::RenderWindow* _window, std::string _texturePath, std::string _texturePath2, sf::Vector2f _initPosition);
	~Enemy();

	void resetPosition();
	void draw();
	void moveEntityLeft(sf::Time& dt) {};
	void moveEntityRight(sf::Time& dt) {};
	sf::Vector2f getRifleBound();

	bool collisionCheck(Bullet& bullet);
	void deathAnimation();
	void toggleTexture();

private:

	//sf::Clock entityClock;
	sf::Texture deathTexture;
	//float moveSpeed = 250.f;
};


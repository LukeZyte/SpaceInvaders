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

	void moveEntity(sf::Time& dt, float gameSpeed = 1);
	sf::Vector2f getRifleBound();

	bool collisionCheck(GraphicalObject* bullet);

private:

	sf::Texture deathTexture;
	float moveSpeed = 50.f;
	bool moveRight = true;

	float stepsPassed = 0;
	float maxStepsToPass = 330.f;
	
};


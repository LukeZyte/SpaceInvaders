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

	//void draw();

	void moveEntity(sf::Time& dt);
	//bool isOutOfBounds();
	//sf::RectangleShape getRectShape() { return rect; }

	//sf::FloatRect hitbox();

	void moveEntityLeft(sf::Time& dt) {};
	void moveEntityRight(sf::Time& dt) {};
	sf::Vector2f getRifleBound() { return sf::Vector2f{ 0.0, 0.0 }; }

	bool collisionCheck(GraphicalObject* bullet) { return false; };
	void deathAnimation() {};

private:
	//sf::RenderWindow* window;
	//sf::RectangleShape rect{ sf::Vector2f(3, 32)};

	float bulletSpeed = 1000.f;
};


#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Bullet
{
public:
	Bullet(sf::RenderWindow* _window, sf::Vector2f _initVec);
	~Bullet();

	void draw();

	void moveBullet(sf::Time& dt);
	bool isOutOfBounds();
	sf::RectangleShape getRectShape() { return rect; }

	sf::FloatRect hitbox();

private:
	sf::RenderWindow* window;
	sf::RectangleShape rect{ sf::Vector2f(3, 32)};


	float bulletSpeed = 1000.f;
};


#include "Bullet.h"

Bullet::Bullet(sf::RenderWindow* _window, sf::Vector2f _initVec)
	: window(_window)
{
	std::cout << "Utworzono Bullet obj!\n";

	// Bullet Init
	rect.setPosition(_initVec);
	rect.setFillColor(sf::Color::Yellow);
	
}

Bullet::~Bullet()
{
	std::cout << "Zniszczono Bullet obj\n";
}

void Bullet::draw()
{
	this->window->draw(rect);
}

void Bullet::moveBullet(sf::Time& dt)
{
	if (rect.getGlobalBounds().top + rect.getGlobalBounds().height > 0)
	{
		rect.move(0.0f, -bulletSpeed * dt.asSeconds());
	}
}

bool Bullet::isOutOfBounds()
{
	if (rect.getGlobalBounds().top + rect.getGlobalBounds().height < 0)
		return true;
	else 
		return false;
}

sf::RectangleShape Bullet::getRect()
{
	return rect;
}
#include "Bullet.h"

Bullet::Bullet(sf::RenderWindow* _window, std::string _texturePath, std::string _texturePath2, sf::Vector2f _initPosition)
	: GraphicalObject(_window, _texturePath, _texturePath2, _initPosition)
{
	resetPosition();
}

Bullet::~Bullet()
{
}

void Bullet::moveEntity(sf::Time& dt, float gameSpeed)
{
	if (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height > 0)
	{
		sprite.move(0.0f, -bulletSpeed * dt.asSeconds());
	}
}

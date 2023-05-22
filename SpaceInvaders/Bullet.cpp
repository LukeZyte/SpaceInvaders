#include "Bullet.h"

Bullet::Bullet(sf::RenderWindow* _window, std::string _texturePath, std::string _texturePath2, sf::Vector2f _initPosition)
	: GraphicalObject(_window, _texturePath, _texturePath2, _initPosition)
{
	std::cout << "Utworzono Bullet obj!\n";

	resetPosition();
	 
}

Bullet::~Bullet()
{
	std::cout << "Zniszczono Bullet obj\n";
}

void Bullet::moveEntity(sf::Time& dt)
{
	if (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height > 0)
	{
		sprite.move(0.0f, -bulletSpeed * dt.asSeconds());
	}
}

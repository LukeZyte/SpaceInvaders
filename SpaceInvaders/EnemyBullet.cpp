#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(sf::RenderWindow* _window, std::string _texturePath, std::string _texturePath2, sf::Vector2f _initPosition)
	: Bullet(_window, _texturePath, _texturePath2, _initPosition)
{

}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::moveEntity(sf::Time& dt)
{
	if (sprite.getGlobalBounds().top < WINDOW_HEIGHT)
	{
		sprite.move(0.0f, bulletSpeed * dt.asSeconds());
	}
}
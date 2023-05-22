#include "Enemy.h"

Enemy::Enemy(sf::RenderWindow* _window, std::string _texturePath, sf::Vector2f _initPosition)
	: GraphicalObject(_window, _texturePath, _initPosition)
{
	resetPosition();
	deathTexture.loadFromFile(ENEMY_DEAD_MODEL_FILEPATH);
}

Enemy::Enemy(sf::RenderWindow* _window, std::string _texturePath, std::string _texturePath2, sf::Vector2f _initPosition)
	: GraphicalObject(_window, _texturePath, _texturePath2, _initPosition)
{
	resetPosition();
	deathTexture.loadFromFile(ENEMY_DEAD_MODEL_FILEPATH);
}

Enemy::~Enemy()
{
	
}

void Enemy::deathAnimation()
{
	sprite.setTexture(deathTexture);
}


bool Enemy::collisionCheck(GraphicalObject* bullet)
{
	if (hitbox().intersects(bullet->hitbox()))
	{
		return true;
	}
	return false;
}

sf::Vector2f Enemy::getRifleBound()
{
	sf::Vector2f vec(sprite.getGlobalBounds().left + (sprite.getGlobalBounds().width / 2), sprite.getGlobalBounds().top + sprite.getGlobalBounds().height);
	return vec;
};


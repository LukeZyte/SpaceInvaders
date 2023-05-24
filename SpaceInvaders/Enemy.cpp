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

void Enemy::moveEntity(sf::Time& dt, float gameSpeed)
{
	stepsPassed += moveSpeed * dt.asSeconds() * gameSpeed;

	if (moveRight && maxStepsToPass > stepsPassed)
	{
		sprite.move(moveSpeed * dt.asSeconds() * gameSpeed, 0.f);
	}

	if (maxStepsToPass < stepsPassed)
	{
		sprite.move(0.f, 30.f);
		stepsPassed = 0;
		moveRight = !moveRight;
	}

	if (!moveRight && maxStepsToPass > stepsPassed)
	{
		sprite.move(-moveSpeed * dt.asSeconds() * gameSpeed, 0.f);
	}
}

float Enemy::getYPos()
{
	return sprite.getGlobalBounds().top + sprite.getGlobalBounds().height;
}
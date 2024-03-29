#include "Player.h"

Player::Player(sf::RenderWindow* _window, std::string _texturePath, sf::Vector2f _initPosition)
	: GraphicalObject(_window, _texturePath, _initPosition)
{
	resetPosition();
}

Player::~Player()
{
}

void Player::moveEntityLeft(sf::Time& dt, float gameSpeed)
{
	if (sprite.getGlobalBounds().left > 0)
	{
		sprite.move(-moveSpeed * dt.asSeconds(), 0.f);
	}
};

void Player::moveEntityRight(sf::Time& dt, float gameSpeed)
{
	if (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width < WINDOW_WIDTH)
	{
		sprite.move(moveSpeed * dt.asSeconds(), 0.f);
	}
};

sf::Vector2f Player::getRifleBound()
{
	sf::Vector2f vec(sprite.getGlobalBounds().left + (sprite.getGlobalBounds().width / 2), sprite.getGlobalBounds().top);
	return vec;
};

bool Player::collisionCheck(GraphicalObject* bullet)
{
	if (hitbox().intersects(bullet->hitbox()))
	{
		return true;
	}
	return false;
}

void Player::resetHP()
{
	HP = 3;
}

void Player::removeHP(int value)
{
	HP = HP - value;
}
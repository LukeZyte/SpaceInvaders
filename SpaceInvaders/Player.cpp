#include "Player.h"

Player::Player(sf::RenderWindow* _window, std::string _texturePath, sf::Vector2f _initPosition)
	: GraphicalObject(_window, _texturePath, _initPosition)
{
	std::cout << "Utworzono Player obj!\n";
	resetPosition();
}

Player::~Player()
{
	std::cout << "Zniszczono Player obj!\n";
}

void Player::draw()
{
	this->window->draw(sprite);
}

void Player::resetPosition()
{
	sprite.setPosition(initPosition.x, initPosition.y);
}

void Player::moveEntityLeft(sf::Time& dt)
{
	if (sprite.getGlobalBounds().left > 0)
	{
		sprite.move(-moveSpeed * dt.asSeconds(), 0.f);
	}
};

void Player::moveEntityRight(sf::Time& dt)
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
	return false;
}
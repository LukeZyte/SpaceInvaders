#include "Player.h"

Player::Player(sf::RenderWindow* _window, std::string _texturePath, sf::Vector2f _initPosition)//, std::vector<Bullet>& _bulletsVec)
	: GraphicalObject(_window, _texturePath, _initPosition)//, bulletsVec(_bulletsVec)
{
	std::cout << "Utworzono Player obj!\n";
}

Player::~Player()
{
	std::cout << "Zniszczono Player obj!\n";
}

void Player::movePlayer(sf::Time& dt, bool moveRight)
{
	if (moveRight && sprite.getGlobalBounds().left + sprite.getGlobalBounds().width < WINDOW_WIDTH)
	{
		sprite.move(moveSpeed * dt.asSeconds(), 0.f);
	} 
	else if (sprite.getGlobalBounds().left > 0)
	{
		sprite.move(-moveSpeed * dt.asSeconds(), 0.f);
	}
};

void Player::update(sf::Time& dt)
{

};

float Player::getTopBound()
{
	return sprite.getGlobalBounds().top;
};

sf::Vector2f Player::getRifleBound()
{
	sf::Vector2f vec(sprite.getGlobalBounds().left + (sprite.getGlobalBounds().width / 2), sprite.getGlobalBounds().top);
	return vec;
};
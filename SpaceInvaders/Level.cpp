#include "Level.h"


Level::Level(sf::RenderWindow& _window) : window(_window)
{
	std::cout << "Utworzono Level obj!\n";

	// Background Init
	texture.loadFromFile(SPACE_BACKGROUND_FILEPATH);
	background.setTexture(texture);
	background2.setTexture(texture);
	background.setPosition(0.f, 0.f);
	background2.setPosition(0.f, -background.getGlobalBounds().height);
}

Level::~Level()
{
	std::cout << "Zniszczono Level obj!\n";
}

void Level::draw()
{
	window.draw(background);
	window.draw(background2);
}

void Level::moveBackgorund(sf::Time& dt, float gameSpeed)
{
	if (bgMoveSpeed <= bgMaxSpeed)
	{
		bgMoveSpeed = bgMoveSpeed + acceleration;
		std::cout << bgMoveSpeed << "\n";
	}

	background.move(0.f, bgMoveSpeed * dt.asSeconds() * gameSpeed * 1.5);
	background2.move(0.f, bgMoveSpeed * dt.asSeconds() * gameSpeed * 1.5);

	// repeating the bg as it moves
	if (background.getGlobalBounds().top > WINDOW_HEIGHT)
	{
		background.setPosition(0.f, -background.getGlobalBounds().height);

	}
	if (background2.getGlobalBounds().top > WINDOW_HEIGHT)
	{
		background2.setPosition(0.f, -background2.getGlobalBounds().height);
	}
}

void Level::stopBackground()
{
	bgMoveSpeed = 0;
}
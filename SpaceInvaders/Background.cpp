#include "Background.h"


Background::Background(sf::RenderWindow& _window) : window(_window)
{
	std::cout << "Utworzono Background obj!\n";

	// Background Init
	texture.loadFromFile(SPACE_BACKGROUND_FILEPATH);
	background.setTexture(texture);
	background2.setTexture(texture);
	background.setPosition(0.f, 0.f);
	background2.setPosition(0.f, -background.getGlobalBounds().height);
}

Background::~Background()
{
	std::cout << "Zniszczono Background obj!\n";
}

void Background::draw()
{
	window.draw(background);
	window.draw(background2);
}

void Background::moveBackgorund(sf::Time& dt, float gameSpeed)
{
	if (bgMoveSpeed <= bgMaxSpeed)
	{
		bgMoveSpeed = bgMoveSpeed + acceleration;
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

void Background::stopBackground()
{
	bgMoveSpeed = 0;
}
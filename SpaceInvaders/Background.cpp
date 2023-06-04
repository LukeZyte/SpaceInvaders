#include "Background.h"


Background::Background(sf::RenderWindow& _window) : window(_window)
{
	// Background Init
	texture.loadFromFile(SPACE_BACKGROUND_FILEPATH);
	background.setTexture(texture);
	background2.setTexture(texture);
	background.setPosition(0.f, 0.f);
	background2.setPosition(0.f, -background.getGlobalBounds().height);
}

Background::~Background()
{
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

	background.move(0.f, bgMoveSpeed * dt.asSeconds() * gameSpeed * 1.5f);
	background2.move(0.f, bgMoveSpeed * dt.asSeconds() * gameSpeed * 1.5f);

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
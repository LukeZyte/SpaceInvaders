#include "Level.h"


Level::Level(sf::RenderWindow& _window) : window(_window)
{
	std::cout << "Utworzono Level obj!\n";

	// Background Init
	


	texture.loadFromFile(SPACE_BACKGROUND_FILEPATH);
	//texture.setRepeated(true);
	background.setTexture(texture);
	//background.setTextureRect(irect);
	//background.setTextureRect(sf::Rect(WINDOW_HEIGHT, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_WIDTH));
	//background2.setTexture(texture);
	//background2.setTextureRect(sf::Rect(WINDOW_HEIGHT, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_WIDTH));
	//background.setPosition(0.f, 0.f);
	//background2.setPosition(0.f, -background.getGlobalBounds().height);
}

Level::~Level()
{
	std::cout << "Zniszczono Level obj!\n";
}

void Level::draw()
{
	window.draw(background);
	//window.draw(background2);
}

void Level::moveBackgorund(sf::Time& dt)
{
	background.move(0.f, bg_move_speed * dt.asSeconds());
	background2.move(0.f, bg_move_speed * dt.asSeconds());

	// repeating the bg as it moves
	if (background.getGlobalBounds().top > WINDOW_HEIGHT)
	{
		//background.setPosition(background2.getGlobalBounds().top + background2.getGlobalBounds().height, 0);
		background.setPosition(0.f, -background.getGlobalBounds().height);

	}
	if (background2.getGlobalBounds().top > WINDOW_HEIGHT)
	{
		//background.setPosition(background.getGlobalBounds().top + background.getGlobalBounds().height, 0);
		background2.setPosition(0.f, -background2.getGlobalBounds().height);
	}
}
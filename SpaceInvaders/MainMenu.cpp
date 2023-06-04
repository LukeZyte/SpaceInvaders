#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow& _window) : window(_window)
{
	// Title Init
	if (!titleFont.loadFromFile(PIXELOIDSANS_FILEPATH))
		std::cout << "Could not load a font file!\n";

	title.setFont(titleFont);
	title.setString("Space Invaders");
	title.setFillColor(sf::Color::Yellow);
	title.setCharacterSize(96);
	title.setStyle(sf::Text::Bold);

	title.setPosition(((float)WINDOW_WIDTH / 2) - (title.getGlobalBounds().width / 2), 100.f);

	// playText Init
	if (!playTextFont.loadFromFile(PIXELOIDSANS_FILEPATH))
		std::cout << "Could not load a font file!\n";

	playText.setFont(playTextFont);
	playText.setString("Press [ SPACE ] to START");
	playText.setFillColor(sf::Color::White);
	playText.setCharacterSize(32);
	playText.setStyle(sf::Text::Bold);

	playText.setPosition(((float)WINDOW_WIDTH / 2) - (playText.getGlobalBounds().width / 2), WINDOW_HEIGHT - 300.f);

	// RecordsText Init
	recordsText.setFont(playTextFont);
	recordsText.setString("Press [ R ] to check records");
	recordsText.setFillColor(sf::Color(255, 255, 255, 180));
	recordsText.setCharacterSize(24);
	recordsText.setStyle(sf::Text::Regular);
	
	recordsText.setPosition(((float)WINDOW_WIDTH / 2) - (recordsText.getGlobalBounds().width / 2), WINDOW_HEIGHT - 400.f);

	// Author Init
	authorText.setFont(playTextFont);
	authorText.setString("Lukasz Jarzab, 2023");
	authorText.setFillColor(sf::Color(255, 255, 255, 180));
	authorText.setCharacterSize(16);
	authorText.setStyle(sf::Text::Regular);

	authorText.setPosition(20.f, WINDOW_HEIGHT - 20.f - authorText.getGlobalBounds().height);

	// Lang Init
	langText.setFont(playTextFont);
	langText.setString("C++ / SFML");
	langText.setFillColor(sf::Color(255, 255, 255, 180));
	langText.setCharacterSize(16);
	langText.setStyle(sf::Text::Regular);
	
	langText.setPosition(WINDOW_WIDTH - 20.f - langText.getGlobalBounds().width, WINDOW_HEIGHT - 20.f - langText.getGlobalBounds().height);
}

MainMenu::~MainMenu()
{
}

void MainMenu::draw()
{
	// Blinking playText
	if (playTextVisible)
	{
		if (playTextClock.getElapsedTime().asSeconds() > textOnTime)
		{
			playText.setPosition(sf::Vector2f{ -100, -100 });
			playTextVisible = !playTextVisible;
			playTextClock.restart();
		}
	}
	else
	{
		if (playTextClock.getElapsedTime().asSeconds() > textOffTime)
		{
			playText.setPosition(((float)WINDOW_WIDTH / 2) - (playText.getGlobalBounds().width / 2), WINDOW_HEIGHT - 300.f);
			playTextVisible = !playTextVisible;
			playTextClock.restart();
		}
	}
	
	// Drawing
	window.draw(title);
	window.draw(authorText);
	window.draw(langText);
	window.draw(playText);
	window.draw(recordsText);
}
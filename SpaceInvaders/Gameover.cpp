#include "Gameover.h"

Gameover::Gameover(sf::RenderWindow& _window) : window(_window)
{
	// Black transparent background
	background.setSize(sf::Vector2f{ WINDOW_WIDTH,WINDOW_HEIGHT });
	background.setFillColor(sf::Color(0, 0, 0, 200));

	if (!mainTextFont.loadFromFile(PIXELOIDSANS_FILEPATH))
		std::cout << "Could not load a font file!\n";

	mainText.setFont(mainTextFont);
	mainText.setString("GAME OVER");
	mainText.setFillColor(sf::Color::Yellow);
	mainText.setCharacterSize(64);
	mainText.setStyle(sf::Text::Bold);

	mainText.setPosition((WINDOW_WIDTH / 2) - (mainText.getGlobalBounds().width / 2), 300.f);

	// playText Init
	if (!playTextFont.loadFromFile(PRESSSTART2P_FILEPATH))
		std::cout << "Could not load a font file!\n";

	playText.setFont(playTextFont);
	playText.setString("Press R to restart!");
	playText.setFillColor(sf::Color::White);
	playText.setCharacterSize(24);
	playText.setStyle(sf::Text::Regular);

	playText.setPosition((WINDOW_WIDTH / 2) - (playText.getGlobalBounds().width / 2), WINDOW_HEIGHT - 400.f);

	// quitText Init
	quitText.setFont(playTextFont);
	quitText.setString("Press Q to Quit to Menu!");
	quitText.setFillColor(sf::Color::White);
	quitText.setCharacterSize(24);
	quitText.setStyle(sf::Text::Regular);

	quitText.setPosition((WINDOW_WIDTH / 2) - (quitText.getGlobalBounds().width / 2), WINDOW_HEIGHT - 450.f);
}

void Gameover::draw()
{
	// Blinking playText
	if (playTextVisible)
	{
		if (playTextClock.getElapsedTime().asSeconds() > textOnTime)
		{
			playText.setPosition(sf::Vector2f{ -100, -100 });
			quitText.setPosition(sf::Vector2f{ -100, -100 });
			playTextVisible = !playTextVisible;
			playTextClock.restart();
		}
	}
	else
	{
		if (playTextClock.getElapsedTime().asSeconds() > textOffTime)
		{
			playText.setPosition((WINDOW_WIDTH / 2) - (playText.getGlobalBounds().width / 2), WINDOW_HEIGHT - 400.f);
			quitText.setPosition((WINDOW_WIDTH / 2) - (quitText.getGlobalBounds().width / 2), WINDOW_HEIGHT - 450.f);
			playTextVisible = !playTextVisible;
			playTextClock.restart();
		}
	}

	// Drawing

	//window.draw(background);
	window.draw(background);
	window.draw(mainText);
	window.draw(playText);
	window.draw(quitText);
}
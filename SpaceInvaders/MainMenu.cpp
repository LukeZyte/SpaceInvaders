#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow& _window) : window(_window)
{
	std::cout << "Utworzono MainMenu obj!\n";

	// Background Init
	//texture.loadFromFile(SPACE_BACKGROUND_FILEPATH);
	//texture.setRepeated(true);
	//background.setTexture(texture);
	//background.setTextureRect(sf::Rect(0, 0, WINDOW_WIDTH, WINDOW_WIDTH ));


	// Title Init
	if (!titleFont.loadFromFile(PIXELOIDSANS_FILEPATH))
		std::cout << "Could not load a font file!\n";

	title.setFont(titleFont);
	title.setString("Space Invaders");
	title.setFillColor(sf::Color::Yellow);
	title.setCharacterSize(96);
	title.setStyle(sf::Text::Bold);

	title.setPosition((WINDOW_WIDTH / 2) - (title.getGlobalBounds().width / 2), 100.f);

	// playText Init
	if (!playTextFont.loadFromFile(PRESSSTART2P_FILEPATH))
		std::cout << "Could not load a font file!\n";

	playText.setFont(playTextFont);
	playText.setString("Press SPACE to start!");
	playText.setFillColor(sf::Color::White);
	playText.setCharacterSize(24);
	playText.setStyle(sf::Text::Regular);

	playText.setPosition((WINDOW_WIDTH / 2) - (playText.getGlobalBounds().width / 2), WINDOW_HEIGHT - 300.f);
}

MainMenu::~MainMenu()
{
	std::cout << "Zniszczono MainMenu obj!\n";
}

void MainMenu::draw()
{
	// Blinking playText
	if (playTextVisible)
	{
		if (playTextClock.getElapsedTime().asSeconds() > textOnTime)
		{
			playText.setCharacterSize(0);
			playTextVisible = !playTextVisible;
			playTextClock.restart();
		}
	}
	else
	{
		if (playTextClock.getElapsedTime().asSeconds() > textOffTime)
		{
			playText.setCharacterSize(24);
			playTextVisible = !playTextVisible;
			playTextClock.restart();
		}
	}
	
	// Drawing

	//window.draw(background);
	window.draw(title);
	window.draw(playText);
}
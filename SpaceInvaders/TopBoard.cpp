#include "TopBoard.h"

TopBoard::TopBoard(sf::RenderWindow& _window) : window(_window)
{
	std::cout << "Utworzono MainMenu obj!\n";

	fontColor = sf::Color::White;

	// LocalFont Init
	if (!localFont.loadFromFile(PIXELOIDSANS_FILEPATH))
		std::cout << "Could not load a font file!\n";

	// Player
	player.setFont(localFont);
	player.setString(playerName);
	player.setFillColor(fontColor);
	player.setStyle(sf::Text::Bold);
	player.setCharacterSize(fontSize);
	player.setPosition(20.f, 5.f);

	// Score
	score.setFont(localFont);
	score.setString("SCORE:  " + std::to_string(playerScore));
	score.setFillColor(fontColor);
	score.setStyle(sf::Text::Bold);
	score.setCharacterSize(fontSize);
	score.setPosition((WINDOW_WIDTH / 2) - (score.getGlobalBounds().width / 2), 5.f);

	// Combo
	combo.setFont(localFont);
	combo.setString("COMBO:  " + std::to_string(playerCombo));
	combo.setFillColor(fontColor);
	combo.setStyle(sf::Text::Bold);
	combo.setCharacterSize(fontSize);
	combo.setPosition(WINDOW_WIDTH - (combo.getGlobalBounds().width) - 20, 5.f);

	// Timer
	timer.setFont(localFont);
	timer.setString(std::to_string(gameTimer));
	timer.setFillColor(fontColor);
	timer.setStyle(sf::Text::Bold);
	timer.setCharacterSize(fontSize);
	timer.setPosition((WINDOW_WIDTH / 2) - (timer.getGlobalBounds().width / 2), 40.f);

}

TopBoard::~TopBoard() {}

void TopBoard::draw()
{
	window.draw(player);
	window.draw(score);
	window.draw(combo);
	window.draw(timer);
}

void TopBoard::setName(std::string name)
{
	playerName = name;
	player.setString(playerName);
	player.setPosition(20.f, 5.f);
}

void TopBoard::setScore(int value)
{
	playerScore = value;
	score.setString("SCORE:  " + std::to_string(playerScore));
	score.setPosition((WINDOW_WIDTH / 2) - (score.getGlobalBounds().width / 2), 5.f);
}

void TopBoard::setCombo(int value)
{
	playerCombo = value;
	combo.setString("COMBO:  " + std::to_string(playerCombo));
	combo.setPosition(WINDOW_WIDTH - (combo.getGlobalBounds().width) - 20, 5.f);
}

void TopBoard::setTimer(int value)
{
	gameTimer = value;
	timer.setString(std::to_string(gameTimer));
	timer.setPosition((WINDOW_WIDTH / 2) - (timer.getGlobalBounds().width / 2), 40.f);
}
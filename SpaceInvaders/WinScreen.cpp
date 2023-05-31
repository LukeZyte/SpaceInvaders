#include "WinScreen.h"

WinScreen::WinScreen(sf::RenderWindow& _window)
	: window(_window)
{
	textFontColor = sf::Color::White;

	// Black transparent background
	background.setSize(sf::Vector2f{ (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT });
	background.setFillColor(sf::Color(0, 0, 0, 200));

	if (!mainTextFont.loadFromFile(PIXELOIDSANS_FILEPATH))
		std::cout << "Could not load a font file!\n";

	// Main text
	mainText.setFont(mainTextFont);
	mainText.setString("YOU WON!");
	mainText.setFillColor(sf::Color::Yellow);
	mainText.setCharacterSize(64);
	mainText.setStyle(sf::Text::Bold);
	mainText.setPosition(((float)WINDOW_WIDTH / 2) - (mainText.getGlobalBounds().width / 2), 200.f);

	mainText2.setFont(mainTextFont);
	mainText2.setString("Congratulations!");
	mainText2.setFillColor(sf::Color::Yellow);
	mainText2.setCharacterSize(42);
	mainText2.setStyle(sf::Text::Bold);
	mainText2.setPosition(((float)WINDOW_WIDTH / 2) - (mainText2.getGlobalBounds().width / 2), 270.f);

	// localFont. Init
	if (!localFont.loadFromFile(PIXELOIDSANS_FILEPATH))
		std::cout << "Could not load a font file!\n";

	playText.setFont(localFont);
	playText.setString("[ R ] Play Again!");
	playText.setFillColor(sf::Color::White);
	playText.setCharacterSize(32);
	playText.setStyle(sf::Text::Bold);
	playText.setPosition(((float)WINDOW_WIDTH / 2) - (playText.getGlobalBounds().width / 2), WINDOW_HEIGHT - 300.f);

	// quitText Init
	quitText.setFont(localFont);
	quitText.setString("<< [ Esc ] Menu");
	quitText.setFillColor(sf::Color::White);
	quitText.setCharacterSize(24);
	quitText.setStyle(sf::Text::Bold);
	quitText.setPosition(100.f, WINDOW_HEIGHT - 300.f);

	////// Score Init //////
	// Player
	player.setFont(localFont);
	player.setString("NICKNAME:  " + playerName);
	player.setFillColor(textFontColor);
	player.setStyle(sf::Text::Regular);
	player.setCharacterSize(fontSize);
	player.setPosition(((float)WINDOW_WIDTH / 2) - (player.getGlobalBounds().width / 2), 400.f);

	// Score
	score.setFont(localFont);
	score.setString("SCORE:  " + std::to_string(playerScore));
	score.setFillColor(textFontColor);
	score.setStyle(sf::Text::Regular);
	score.setCharacterSize(fontSize);
	score.setPosition(((float)WINDOW_WIDTH / 2) - (score.getGlobalBounds().width / 2), 450.f);

	// Combo
	combo.setFont(localFont);
	combo.setString("MAX COMBO:  " + std::to_string(playerMaxCombo));
	combo.setFillColor(textFontColor);
	combo.setStyle(sf::Text::Regular);
	combo.setCharacterSize(fontSize);
	combo.setPosition(((float)WINDOW_WIDTH / 2) - (combo.getGlobalBounds().width / 2), 500.f);

	// Timer
	timer.setFont(localFont);
	timer.setString("TIME:  " + std::to_string(gameTimer));
	timer.setFillColor(textFontColor);
	timer.setStyle(sf::Text::Regular);
	timer.setCharacterSize(fontSize);
	timer.setPosition(((float)WINDOW_WIDTH / 2) - (timer.getGlobalBounds().width / 2), 550.f);

	// NewRecord Text
	newRecordText.setFont(mainTextFont);
	newRecordText.setString("NEW RECORD!");
	newRecordText.setFillColor(sf::Color::Magenta);
	newRecordText.setCharacterSize(36);
	newRecordText.setStyle(sf::Text::Bold);
	newRecordText.setPosition(((float)WINDOW_WIDTH / 2) - (newRecordText.getGlobalBounds().width / 2), 330.f);
}

WinScreen::~WinScreen()
{

}

void WinScreen::draw()
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
	window.draw(background);
	window.draw(mainText);
	window.draw(mainText2);
	window.draw(playText);
	window.draw(quitText);
	window.draw(player);
	window.draw(score);
	window.draw(combo);
	window.draw(timer);
	if (newRecord)
	{
		window.draw(newRecordText);
	}
}

void WinScreen::setValues(std::string _pName, int _pScore, int _pCombo, int _gTimer)
{
	playerName = _pName;
	playerScore = _pScore;
	playerMaxCombo = _pCombo;
	gameTimer = _gTimer;

	player.setString("NICKNAME:  " + playerName);
	player.setPosition(((float)WINDOW_WIDTH / 2) - (player.getGlobalBounds().width / 2), 400.f);
	score.setString("SCORE:  " + std::to_string(playerScore));
	score.setPosition(((float)WINDOW_WIDTH / 2) - (score.getGlobalBounds().width / 2), 450.f);
	combo.setString("MAX COMBO:  " + std::to_string(playerMaxCombo));
	combo.setPosition(((float)WINDOW_WIDTH / 2) - (combo.getGlobalBounds().width / 2), 500.f);
	timer.setString("TIME:  " + std::to_string(gameTimer));
	timer.setPosition(((float)WINDOW_WIDTH / 2) - (timer.getGlobalBounds().width / 2), 550.f);
}

void WinScreen::setNewRecord(bool _newRecord)
{
	newRecord = _newRecord;
}
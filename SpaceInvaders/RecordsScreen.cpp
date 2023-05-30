#include "RecordsScreen.h"

RecordsScreen::RecordsScreen(sf::RenderWindow& _window) : window(_window)
{
	textFontColor = sf::Color::White;

	if (!mainTextFont.loadFromFile(PIXELOIDSANS_FILEPATH))
		std::cout << "Could not load a font file!\n";

	// localFont. Init
	if (!localFont.loadFromFile(PIXELOIDSANS_FILEPATH))
		std::cout << "Could not load a font file!\n";

	// quitText Init
	quitText.setFont(localFont);
	quitText.setString("<< [ Esc ] Back");
	quitText.setFillColor(sf::Color::White);
	quitText.setCharacterSize(24);
	quitText.setStyle(sf::Text::Bold);
	quitText.setPosition(100.f, WINDOW_HEIGHT - 200.f);

	// Available / Unavailable Init
	bestUnavailable.setFont(localFont);
	bestUnavailable.setString("No best record found!");
	bestUnavailable.setFillColor(sf::Color::Magenta);
	bestUnavailable.setCharacterSize(fontSize);
	bestUnavailable.setStyle(sf::Text::Regular);
	bestUnavailable.setPosition(((float)WINDOW_WIDTH / 2) - (bestUnavailable.getGlobalBounds().width / 2), 340.f);

	lastUnavailable.setFont(localFont);
	lastUnavailable.setString("No last record found!");
	lastUnavailable.setFillColor(sf::Color::Magenta);
	lastUnavailable.setCharacterSize(fontSize);
	lastUnavailable.setStyle(sf::Text::Regular);
	lastUnavailable.setPosition(((float)WINDOW_WIDTH / 2) - (lastUnavailable.getGlobalBounds().width / 2), 640.f);

	// Main texts
	mainText.setFont(mainTextFont);
	mainText.setString("BEST RECORD");
	mainText.setFillColor(sf::Color::Yellow);
	mainText.setCharacterSize(48);
	mainText.setStyle(sf::Text::Bold);
	mainText.setPosition(((float)WINDOW_WIDTH / 2) - (mainText.getGlobalBounds().width / 2), 200.f);

	mainText2.setFont(mainTextFont);
	mainText2.setString("LAST RECORD");
	mainText2.setFillColor(sf::Color::Yellow);
	mainText2.setCharacterSize(32);
	mainText2.setStyle(sf::Text::Regular);
	mainText2.setPosition(((float)WINDOW_WIDTH / 2) - (mainText2.getGlobalBounds().width / 2), 500.f);

	////// BEST Score Init //////
	// Player
	player.setFont(localFont);
	player.setString("NICKNAME:  " + playerName);
	player.setFillColor(textFontColor);
	player.setStyle(sf::Text::Regular);
	player.setCharacterSize(fontSize);
	player.setPosition(((float)WINDOW_WIDTH / 2) - (player.getGlobalBounds().width / 2), 300.f);

	// Score
	score.setFont(localFont);
	score.setString("SCORE:  " + playerScore);
	score.setFillColor(textFontColor);
	score.setStyle(sf::Text::Regular);
	score.setCharacterSize(fontSize);
	score.setPosition(((float)WINDOW_WIDTH / 2) - (score.getGlobalBounds().width / 2), 340.f);

	// Combo
	maxCombo.setFont(localFont);
	maxCombo.setString("MAX COMBO:  " + playerMaxCombo);
	maxCombo.setFillColor(textFontColor);
	maxCombo.setStyle(sf::Text::Regular);
	maxCombo.setCharacterSize(fontSize);
	maxCombo.setPosition(((float)WINDOW_WIDTH / 2) - (maxCombo.getGlobalBounds().width / 2), 380.f);

	// Timer
	timer.setFont(localFont);
	timer.setString("TIME:  " + gameTimer);
	timer.setFillColor(textFontColor);
	timer.setStyle(sf::Text::Regular);
	timer.setCharacterSize(fontSize);
	timer.setPosition(((float)WINDOW_WIDTH / 2) - (timer.getGlobalBounds().width / 2), 420.f);

	////// LAST Score Init //////
	// Player
	lastPlayer.setFont(localFont);
	lastPlayer.setString("NICKNAME:  " + playerName);
	lastPlayer.setFillColor(textFontColor);
	lastPlayer.setStyle(sf::Text::Regular);
	lastPlayer.setCharacterSize(fontSize);
	lastPlayer.setPosition(((float)WINDOW_WIDTH / 2) - (lastPlayer.getGlobalBounds().width / 2), 600.f);

	// Score
	lastScore.setFont(localFont);
	lastScore.setString("SCORE:  " + playerScore);
	lastScore.setFillColor(textFontColor);
	lastScore.setStyle(sf::Text::Regular);
	lastScore.setCharacterSize(fontSize);
	lastScore.setPosition(((float)WINDOW_WIDTH / 2) - (lastScore.getGlobalBounds().width / 2), 640.f);

	// Combo
	lastMaxCombo.setFont(localFont);
	lastMaxCombo.setString("MAX COMBO:  " + playerMaxCombo);
	lastMaxCombo.setFillColor(textFontColor);
	lastMaxCombo.setStyle(sf::Text::Regular);
	lastMaxCombo.setCharacterSize(fontSize);
	lastMaxCombo.setPosition(((float)WINDOW_WIDTH / 2) - (lastMaxCombo.getGlobalBounds().width / 2), 680.f);

	// Timer
	lastTimer.setFont(localFont);
	lastTimer.setString("TIME:  " + gameTimer);
	lastTimer.setFillColor(textFontColor);
	lastTimer.setStyle(sf::Text::Regular);
	lastTimer.setCharacterSize(fontSize);
	lastTimer.setPosition(((float)WINDOW_WIDTH / 2) - (lastTimer.getGlobalBounds().width / 2), 720.f);
}

void RecordsScreen::draw()
{
	// Drawing
	window.draw(mainText);

	if (availableBestRecord)
	{
		window.draw(player);
		window.draw(score);
		window.draw(maxCombo);
		window.draw(timer);
	}
	else 
	{
		window.draw(bestUnavailable);
	}

	window.draw(mainText2);

	if (availableLastRecord)
	{
		window.draw(lastPlayer);
		window.draw(lastScore);
		window.draw(lastMaxCombo);
		window.draw(lastTimer);
	}
	else
	{
		window.draw(lastUnavailable);
	}

	window.draw(quitText);
}

void RecordsScreen::setRecordValues(std::string _pName, std::string _pScore, std::string _pMaxCombo, std::string _gTimer)
{
	playerName = _pName;
	playerScore = _pScore;
	playerMaxCombo = _pMaxCombo;
	gameTimer = _gTimer;

	player.setString("NICKNAME:  " + playerName);
	player.setPosition(((float)WINDOW_WIDTH / 2) - (player.getGlobalBounds().width / 2), 300.f);
	score.setString("SCORE:  " + playerScore);
	score.setPosition(((float)WINDOW_WIDTH / 2) - (score.getGlobalBounds().width / 2), 340.f);
	maxCombo.setString("MAX COMBO:  " + playerMaxCombo);
	maxCombo.setPosition(((float)WINDOW_WIDTH / 2) - (maxCombo.getGlobalBounds().width / 2), 380.f);
	timer.setString("TIME:  " + gameTimer);
	timer.setPosition(((float)WINDOW_WIDTH / 2) - (timer.getGlobalBounds().width / 2), 420.f);
}

void RecordsScreen::setLastValues(std::string _pName, std::string _pScore, std::string _pMaxCombo, std::string _gTimer)
{
	lastPlayerName = _pName;
	lastPlayerScore = _pScore;
	lastPlayerMaxCombo = _pMaxCombo;
	lastGameTimer = _gTimer;

	lastPlayer.setString("NICKNAME:  " + lastPlayerName);
	lastPlayer.setPosition(((float)WINDOW_WIDTH / 2) - (lastPlayer.getGlobalBounds().width / 2), 600.f);
	lastScore.setString("SCORE:  " + lastPlayerScore);
	lastScore.setPosition(((float)WINDOW_WIDTH / 2) - (lastScore.getGlobalBounds().width / 2), 640.f);
	lastMaxCombo.setString("MAX COMBO:  " + lastPlayerMaxCombo);
	lastMaxCombo.setPosition(((float)WINDOW_WIDTH / 2) - (lastMaxCombo.getGlobalBounds().width / 2), 680.f);
	lastTimer.setString("TIME:  " + lastGameTimer);
	lastTimer.setPosition(((float)WINDOW_WIDTH / 2) - (lastTimer.getGlobalBounds().width / 2), 720.f);
}
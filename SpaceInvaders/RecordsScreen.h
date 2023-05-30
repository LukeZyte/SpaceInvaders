#pragma once

import Globals;

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class RecordsScreen
{
public:
	RecordsScreen(sf::RenderWindow& _window);
	~RecordsScreen() {};

	void draw();
	void setRecordValues(std::string _pName, std::string _pScore, std::string _pMaxCombo, std::string _gTimer);
	void setLastValues(std::string _pName, std::string _pScore, std::string _pMaxCombo, std::string _gTimer);
	void setUnavailableLastRecord() { availableLastRecord = false; }
	void setAvailableLastRecord() { availableLastRecord = true; }
	void setUnavailableBestRecord() { availableBestRecord = false; }
	void setAvailableBestRecord() { availableBestRecord = true; }

private:
	sf::RenderWindow& window;

	sf::Font mainTextFont;
	sf::Text mainText;
	sf::Text mainText2;

	sf::Color fontColor;
	sf::Text quitText;

	sf::Color textFontColor;
	sf::Font localFont;
	sf::Text player;
	sf::Text score;
	sf::Text maxCombo;
	sf::Text timer;
	sf::Text lastPlayer;
	sf::Text lastScore;
	sf::Text lastMaxCombo;
	sf::Text lastTimer;
	int fontSize = 20;
	sf::Text lastUnavailable;
	sf::Text bestUnavailable;

	bool availableLastRecord = true;
	bool availableBestRecord = true;

	// Best
	std::string playerName = "";
	std::string playerScore = "";
	std::string playerMaxCombo = "";
	std::string gameTimer = "";

	// Last
	std::string lastPlayerName = "";
	std::string lastPlayerScore = "";
	std::string lastPlayerMaxCombo = "";
	std::string lastGameTimer = "";

};


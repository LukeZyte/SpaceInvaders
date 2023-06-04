#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

import Globals;

class WinScreen
{
public:
	WinScreen(sf::RenderWindow& _window);
	~WinScreen();

	void draw();
	void setValues(std::string _pName, int _pScore, int _pCombo, int _gTimer);
	void setNewRecord(bool _newRecord);

private:
	sf::RenderWindow& window;

	sf::RectangleShape background;
	sf::Font mainTextFont;
	sf::Text mainText;
	sf::Font mainText2Font;
	sf::Text mainText2;

	sf::Color fontColor;
	sf::Text playText;
	sf::Text quitText;
	bool playTextVisible = true;
	sf::Clock playTextClock;
	float textOnTime = 1.5f;
	float textOffTime = 0.8f;

	sf::Color textFontColor;
	sf::Font localFont;
	sf::Text player;
	sf::Text score;
	sf::Text combo;
	sf::Text timer;
	int fontSize = 28;

	std::string playerName = "";
	int playerScore = 0;
	int playerMaxCombo = 0;
	int gameTimer = 0;

	bool newRecord = false;
	sf::Text newRecordText;
};  


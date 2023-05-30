#pragma once

//#include "Globals.h"
import Globals;

#include <SFML/Graphics.hpp>
#include <iostream>

class WinScreen
{
public:
	WinScreen(sf::RenderWindow& _window);
	~WinScreen();

	void draw();
	void setValues(std::string _pName, int _pScore, int _pCombo, int _gTimer);

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
	float textOnTime = 1.5;
	float textOffTime = 0.8;

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
};  

#pragma once

//#include "Globals.h"
import Globals;

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <algorithm>

class TopBoard
{
public:
	TopBoard(sf::RenderWindow& _window);
	~TopBoard();

	void draw();
	void setName(std::string name);
	void setScore(int value);
	void setCombo(int value);
	void setTimer(int value);

private:
	sf::RenderWindow& window;

	sf::Color fontColor;
	sf::Font localFont;
	sf::Text player;
	sf::Text score;
	sf::Text combo;
	sf::Text timer;
	int fontSize = 24;

	std::string playerName = "";
	int playerScore = 0;
	int playerCombo = 0;
	int gameTimer = 0;
};


#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

import Globals;

class MainMenu
{
public:
	MainMenu(sf::RenderWindow& _window);
	~MainMenu();

	void draw();

private:
	sf::RenderWindow& window;

	sf::Font titleFont;
	sf::Text title;
	sf::Text authorText;
	sf::Text langText;

	sf::Font playTextFont;
	sf::Text playText;
	sf::Text recordsText;
	bool playTextVisible = true;
	sf::Clock playTextClock;
	float textOnTime = 1.5f;
	float textOffTime = 0.8f;

};


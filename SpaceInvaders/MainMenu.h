#pragma once

//#include "Globals.h"
import Globals;

#include <iostream>
#include <SFML/Graphics.hpp>

class MainMenu
{
public:
	MainMenu(sf::RenderWindow& _window);
	~MainMenu();

	void draw();

private:
	sf::RenderWindow& window;

	//sf::Texture texture;
	//sf::Sprite background;
	sf::Font titleFont;
	sf::Text title;
	sf::Text authorText;

	sf::Font playTextFont;
	sf::Text playText;
	sf::Text recordsText;
	bool playTextVisible = true;
	sf::Clock playTextClock;
	float textOnTime = 1.5;
	float textOffTime = 0.8;

};


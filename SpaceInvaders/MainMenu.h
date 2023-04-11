#pragma once

#include "Globals.h"

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

	sf::Font playTextFont;
	sf::Text playText;
	bool playTextVisible = true;
	sf::Clock playTextClock;
	float textOnTime = 1;
	float textOffTime = 0.5;

};


#pragma once


#include <SFML/Graphics.hpp>
#include <iostream>
#include <regex>
#include <cctype>

import Globals;

class NicknameScreen
{
public:
	NicknameScreen(sf::RenderWindow& _window);
	~NicknameScreen();

	void draw();
	void updateNickname(sf::Event event);
	void updateNickname();
	std::string getNickname() { return inputNicknameText.getString(); }
	void resetNickname();

private:
	sf::RenderWindow& window;

	sf::Font localFont;
	sf::Color textFontColor;
	sf::Color fontColor;
	
	sf::Text mainText;
	sf::String inputNickname;
	sf::Text inputNicknameText;

	sf::Text enterText;
	sf::Text quitText;
};


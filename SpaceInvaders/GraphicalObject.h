#pragma once

#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

import Globals;

class GraphicalObject
{
public:
	GraphicalObject(sf::RenderWindow* _window, std::string _texturePath, sf::Vector2f _initPosition);
	GraphicalObject(sf::RenderWindow* _window, std::string _texturePath, std::string _texturePath2, sf::Vector2f _initPosition);
	~GraphicalObject();

	void resetPosition();
	void draw();
	void toggleTexture();
	bool isOutOfBounds();

	sf::FloatRect hitbox();

	sf::Sprite* getSprite() { return &sprite; }
	void setTextureFrameIndex(int newIndex);
	int getTextureFrameIndex() { return textureFrameIndex; }

protected:
	sf::RenderWindow* window;
	std::string texturePath;
	std::string texturePath2;
	sf::Vector2f initPosition;

	std::array<sf::Texture, 2> textures;
	sf::Sprite sprite;
	int textureFrameIndex = 0;
};


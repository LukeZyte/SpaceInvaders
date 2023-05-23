#pragma once

#include "Globals.h"

#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

class GraphicalObject
{
public:
	GraphicalObject(sf::RenderWindow* _window, std::string _texturePath, sf::Vector2f _initPosition);
	GraphicalObject(sf::RenderWindow* _window, std::string _texturePath, std::string _texturePath2, sf::Vector2f _initPosition);
	~GraphicalObject();

	void resetPosition();
	void draw();
	virtual void moveEntityLeft(sf::Time& dt, float gameSpeed) = 0;
	virtual void moveEntityRight(sf::Time& dt, float gameSpeed) = 0;
	virtual void moveEntity(sf::Time& dt, float gameSpeed = 1) = 0;
	virtual sf::Vector2f getRifleBound() = 0;

	virtual bool collisionCheck(GraphicalObject* bullet) = 0;
	virtual void deathAnimation() = 0;
	void toggleTexture();
	bool isOutOfBounds();

	sf::FloatRect hitbox();

	sf::Sprite* getSprite() { return &sprite; }
	//sf::Texture getTexture() { return texture; }
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


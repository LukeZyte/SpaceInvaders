#pragma once

#include "Globals.h"
#include "Bullet.h"

#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

class GraphicalObject
{
public:
	GraphicalObject(sf::RenderWindow* _window, std::string _texturePath, sf::Vector2f _initPosition);
	GraphicalObject(sf::RenderWindow* _window, std::string _texturePath, std::string _texturePath2, sf::Vector2f _initPosition);
	~GraphicalObject();

	virtual void resetPosition() = 0;
	virtual void draw() = 0;
	virtual void moveEntityLeft(sf::Time& dt) = 0;
	virtual void moveEntityRight(sf::Time& dt) = 0;
	virtual sf::Vector2f getRifleBound() = 0;

	virtual bool collisionCheck(Bullet& bullet) = 0;
	virtual void deathAnimation() = 0;
	virtual void toggleTexture() = 0;

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


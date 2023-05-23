#include "GraphicalObject.h"

GraphicalObject::GraphicalObject(sf::RenderWindow* _window, std::string _texturePath, sf::Vector2f _initPosition) 
	: window(_window), texturePath(_texturePath), initPosition(_initPosition)
{
	// Player Init
	textures[0].loadFromFile(texturePath);
	textures[1].loadFromFile(texturePath);
	sprite.setTexture(textures[textureFrameIndex]);
	
	//resetPosition();
}

GraphicalObject::GraphicalObject(sf::RenderWindow* _window, std::string _texturePath, std::string _texturePath2, sf::Vector2f _initPosition)
	: window(_window), texturePath(_texturePath), texturePath2(_texturePath2), initPosition(_initPosition)
{
	// Player Init
	textures[0].loadFromFile(_texturePath);
	textures[1].loadFromFile(_texturePath2);
	sprite.setTexture(textures[textureFrameIndex]);

	//resetPosition();
}

GraphicalObject::~GraphicalObject()
{
}

sf::FloatRect GraphicalObject::hitbox()
{
	sf::FloatRect fRect(
		sprite.getGlobalBounds().left,
		sprite.getGlobalBounds().top,
		sprite.getGlobalBounds().width,
		sprite.getGlobalBounds().height
	);
	return fRect;
}

void GraphicalObject::setTextureFrameIndex(int newIndex)
{
	textureFrameIndex = newIndex;
}

bool GraphicalObject::isOutOfBounds()
{
	if ((sprite.getGlobalBounds().top + sprite.getGlobalBounds().height < 0) || (sprite.getGlobalBounds().top > WINDOW_HEIGHT))
		return true;
	else
		return false;
}

void GraphicalObject::resetPosition()
{
	sprite.setPosition(initPosition.x, initPosition.y);
};


void GraphicalObject::draw()
{
	this->window->draw(sprite);
}

void GraphicalObject::toggleTexture()
{
	if (textureFrameIndex == 0)
	{
		getSprite()->setTexture(textures[1]);
		setTextureFrameIndex(1);
	}
	else
	{
		getSprite()->setTexture(textures[0]);
		setTextureFrameIndex(0);
	}
}
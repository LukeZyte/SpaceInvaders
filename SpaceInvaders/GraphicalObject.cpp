#include "GraphicalObject.h"

GraphicalObject::GraphicalObject(sf::RenderWindow* _window, std::string _texturePath, sf::Vector2f _initPosition) 
	: window(_window), texturePath(_texturePath), initPosition(_initPosition)
{
	std::cout << "Utworzono GraphicalObject obj!\n";

	// Player Init
	textures[0].loadFromFile(_texturePath);
	textures[1].loadFromFile(_texturePath);
	sprite.setTexture(textures[textureFrameIndex]);
	
	//resetPosition();
}

GraphicalObject::GraphicalObject(sf::RenderWindow* _window, std::string _texturePath, std::string _texturePath2, sf::Vector2f _initPosition)
	: window(_window), texturePath(_texturePath), texturePath2(_texturePath2), initPosition(_initPosition)
{
	std::cout << "Utworzono GraphicalObject obj!\n";

	// Player Init
	textures[0].loadFromFile(_texturePath);
	textures[1].loadFromFile(_texturePath2);
	sprite.setTexture(textures[textureFrameIndex]);

	//resetPosition();
}

GraphicalObject::~GraphicalObject()
{
	std::cout << "Zniszczono GraphicalOject obj!\n";
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

//void GraphicalObject::resetPosition()
//{
//	sprite.setPosition(initPosition.x, initPosition.y);
//};


//void GraphicalObject::draw()
//{
//	this->window->draw(sprite);
//}

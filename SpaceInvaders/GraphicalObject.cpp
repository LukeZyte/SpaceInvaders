#include "GraphicalObject.h"

GraphicalObject::GraphicalObject(sf::RenderWindow* _window, std::string _texturePath, sf::Vector2f _initPosition) 
	: window(_window), texturePath(_texturePath), initPosition(_initPosition)
{
	std::cout << "Utworzono GraphicalObject obj!\n";

	// Player Init
	texture.loadFromFile(_texturePath);
	sprite.setTexture(texture);
	
	//resetPosition();
}

GraphicalObject::~GraphicalObject()
{
	std::cout << "Zniszczono GraphicalOject obj!\n";
}

//void GraphicalObject::resetPosition()
//{
//	sprite.setPosition(initPosition.x, initPosition.y);
//};


//void GraphicalObject::draw()
//{
//	this->window->draw(sprite);
//}

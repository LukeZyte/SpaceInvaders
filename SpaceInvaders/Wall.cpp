#include "Wall.h"

Wall::Wall(sf::RenderWindow* _window, std::string _texturePath, sf::Vector2f _initPosition)
	: GraphicalObject(_window, _texturePath, _initPosition)
{
	resetPosition();
	tex.loadFromFile(BULLET_LIGHT_FILEPATH);
}

Wall::~Wall()
{

}

bool Wall::collisionCheck(GraphicalObject* bullet)
{
	if (hitbox().intersects(bullet->hitbox()))
	{
		return true;
	}
	return false;
}

void Wall::changeTexture()
{
	if (HP == 5)
	{
		tex.loadFromFile(WALL_FULL_FILEPATH);
	}
	else if (HP == 4)
	{
		tex.loadFromFile(WALL_4_FILEPATH);
	}
	else if (HP == 3)
	{
		tex.loadFromFile(WALL_3_FILEPATH);
	}
	else if (HP == 2)
	{
		tex.loadFromFile(WALL_2_FILEPATH);
	}
	else if (HP == 1)
	{
		tex.loadFromFile(WALL_1_FILEPATH);
	}
	sprite.setTexture(tex);
}

void Wall::hit()
{
	HP--;
}
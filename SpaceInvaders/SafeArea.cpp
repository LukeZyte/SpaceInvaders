#include "SafeArea.h"

SafeArea::SafeArea(sf::RenderWindow* _window, std::string _texturePath, sf::Vector2f _initPosition)
	: GraphicalObject(_window, _texturePath, _initPosition)
{
	// SafeArea Init
	safeAreaTex.loadFromFile(texturePath);
	safeAreaSprite.setTexture(safeAreaTex);
	safeAreaSprite.setPosition(sf::Vector2f(0.f, 840.f));
}

void SafeArea::draw()
{
	window->draw(safeAreaSprite);
}

bool SafeArea::collisionCheck(Enemy* enemy)
{
	if (hitbox().intersects(enemy->hitbox()))
	{
		return true;
	}
	return false;
}
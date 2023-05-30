#pragma once

#include "GraphicalObject.h"
//#include "Globals.h"
import Globals;
#include "Enemy.h"

#include <SFML/Graphics.hpp>
#include <iostream>

class SafeArea :
    public GraphicalObject
{
public:
    SafeArea(sf::RenderWindow* _window, std::string _texturePath, sf::Vector2f _initPosition);
    ~SafeArea() {};

    void draw();
    bool collisionCheck(Enemy* enemy);

private:
    sf::Texture safeAreaTex;
    sf::Sprite safeAreaSprite;
};


#pragma once

#include "GraphicalObject.h"
#include "Enemy.h"

#include <SFML/Graphics.hpp>
#include <iostream>

import Globals;

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


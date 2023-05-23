#pragma once

#include "Bullet.h"

class EnemyBullet :
    public Bullet
{
public:
    EnemyBullet(sf::RenderWindow* _window, std::string _texturePath, std::string _texturePath2, sf::Vector2f _initPosition);
    ~EnemyBullet();

    void moveEntity(sf::Time& dt, float gameSpeed = 1);
private:
    float bulletSpeed = 300.0f;
};


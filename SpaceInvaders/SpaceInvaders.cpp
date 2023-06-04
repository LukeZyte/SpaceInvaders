#include "Game.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

import Globals;

// Things from C++20 used:
/*
    regex
    modules
    ranges
    filesystem
*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Invaders");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(FPS_LIMIT);

    Game* game = new Game(window);
    game->gameLoop();

    delete game;
    return EXIT_SUCCESS;
}

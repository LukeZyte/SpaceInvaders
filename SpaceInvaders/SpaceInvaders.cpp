#include "Game.h"
#include "Globals.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Invaders");
    // window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(FPS_LIMIT);

    Game game(window);
    game.gameLoop();

    return EXIT_SUCCESS;
}

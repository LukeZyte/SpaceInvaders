#include "Game.h"

Game::Game(sf::RenderWindow& _window) 
    : window(_window), gameState("menu")
{
    //window.setFramerateLimit(FPS_LIMIT);
    std::cout << "Game window addr: " << &window << "\n";

    gameLoop();
}

Game::~Game()
{
    std::cout << "Usunieto instancje MainMenu z Game.h\n";
}

void Game::draw()
{
    if (gameState == "menu")
    {
        mainMenu.draw();
        player.draw();
    }
    else if (gameState == "game")
    {
        player.draw();
    }
    //level.draw();
    //player.draw();
    //mainMenu.draw();
}

void Game::gameLoop()
{
    sf::Clock clock;
    //sf::Clock appClock;

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        sf::Event event;

        //std::cout << "Time step: " << dt.asSeconds() << '\n';
        //std::cout << appClock.getElapsedTime().asSeconds() << "\n";

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gameState == "menu")
        {
            gameState = "game";
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && gameState == "game") {
            player.movePlayer(dt, false);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && gameState == "game") {
            player.movePlayer(dt, true);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gameState == "game") {
            if (reloadClock.getElapsedTime().asSeconds() > reloadTime)
            {
                playerShots();
                reloadClock.restart();
            }
        }

        window.clear();
        std::cout << "bulletsVec size: " << playerBulletsVec.size() << "\n";
        //mainMenu.draw();
        //level.moveBackgorund(dt);
        //erasePlayerShots();

        erasePlayerShots();

        for (auto& bullet : playerBulletsVec)
        {
            //window.draw(bullet.getRect());
            bullet.draw();
            bullet.moveBullet(dt);
        }
        draw();
        window.display();
    }
}

void Game::playerShots()
{
    Bullet bullet(&window, player.getRifleBound());
    playerBulletsVec.push_back(bullet);
}

void Game::erasePlayerShots()
{
    for (int i = 0; i < playerBulletsVec.size(); i++)
    {
        if (playerBulletsVec[i].isOutOfBounds())
        {
            playerBulletsVec.erase(playerBulletsVec.begin() + i);
            break;
        }
    }
}

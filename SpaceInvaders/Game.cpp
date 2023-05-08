#include "Game.h"

Game::Game(sf::RenderWindow& _window) 
    : window(_window), gameState("menu")
{
    std::cout << "Game window addr: " << &window << "\n";

    gameLoop();
}

Game::~Game()
{
    std::cout << "Usunieto instancje MainMenu z Game.h\n";
}

void Game::draw(sf::Time& dt)
{
    if (gameState == "menu")
    {
        mainMenu.draw();
        player->draw();
    }
    else if (gameState == "game")
    {
        clocksHandler();

        level.draw();
        level.moveBackgorund(dt);
        player->draw();
        drawEnemies();
        checkCollisions();
    }
}

void Game::clocksHandler()
{
    //std::cout << enemiesAnimationClock.getElapsedTime().asSeconds() << " clocksHandler inited!\n";
    if (enemiesAnimationClock.getElapsedTime().asSeconds() > enemiesAnimationTimer)
    {
        enemiesAnimationClock.restart();
        animateAliens();
    }
    else {

    }
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
            initGame();
            gameState = "game";
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && gameState == "game") {
            player->moveEntityLeft(dt);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && gameState == "game") {
            player->moveEntityRight(dt);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gameState == "game") {
            if (reloadClock.getElapsedTime().asSeconds() > reloadTime)
            {
                playerShots();
                reloadClock.restart();
            }
        }

        window.clear();

        erasePlayerShots();
        level.draw();
        draw(dt);
        for (auto& bullet : playerBulletsVec)
        {
            bullet.draw();
            bullet.moveBullet(dt);
        }
        window.display();
    }
}

void Game::initGame()
{
    for (int i = 100; i < WINDOW_WIDTH - 100; i = i + 120)
    {
        GraphicalObject* enemy = new Enemy(&window, ALIENTEXTURE_MODEL_FILEPATH, ALIENTEXUTRE_2_MODEL_FILEPATH, sf::Vector2f(i, 200.f));
        enemiesVec.push_back(enemy);
    }
}

void Game::playerShots()
{
    Bullet bullet(&window, player->getRifleBound());
    playerBulletsVec.push_back(bullet);

    std::cout << "bulletsVec size: " << playerBulletsVec.size() << "\n";
}

void Game::erasePlayerShots()
{
    for (int i = 0; i < playerBulletsVec.size(); i++)
    {
        if (playerBulletsVec[i].isOutOfBounds())
        {
            playerBulletsVec.erase(playerBulletsVec.begin() + i);
            std::cout << "bulletsVec size: " << playerBulletsVec.size() << "\n";
            break;
        }
    }
}

void Game::drawEnemies()
{
    for (auto& enemy : enemiesVec)
    {
        enemy->draw();
    }
}

void Game::checkCollisions()
{
    for (int ie = 0; ie < enemiesVec.size(); ie++)
    {
        for (int ib = 0; ib < playerBulletsVec.size(); ib++)
        {
            if (enemiesVec[ie]->collisionCheck(playerBulletsVec[ib]))
            {
                std::cout << "enemiesVecSize: " << enemiesVec.size() << std::endl;
                playerBulletsVec.erase(playerBulletsVec.begin() + ib);
                enemiesVec.erase(enemiesVec.begin() + ie);
            }
        }
    }
}

void Game::deleteDeadBodies()
{

}

void Game::animateAliens()
{
    std::cout << "Change!\n";
    for (int i = 0; i < enemiesVec.size(); i++)
    {
        enemiesVec[i]->toggleTexture();
    }
}
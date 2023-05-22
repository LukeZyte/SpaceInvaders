#include "Game.h"

Game::Game(sf::RenderWindow& _window) 
    : window(_window), gameState("menu")
{
    std::cout << "Game window addr: " << &window << "\n";

    gameLoop();
}

Game::~Game()
{
    std::cout << "Usunieto instancje Game z Game.h\n";
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
        player->draw();
        drawEnemies();
        alienShots();
        checkCollisions();
    }
    else if (gameState == "gameover")
    {
        level.draw();
        player->draw();
        drawEnemies();
        alienShots();
        checkCollisions();
        gameover.draw();
    }
}

void Game::moveElements(sf::Time& dt)
{
    if (!lockMovement)
    {
        level.moveBackgorund(dt);
        for (auto& bullet : playerBulletsVec)
        {
            bullet->draw();
            bullet->moveEntity(dt);
        }
        for (auto& bullet : enemyBulletsVec)
        {
            bullet->draw();
            bullet->moveEntity(dt);
        }
    }
}

void Game::clocksHandler()
{
    if (enemiesAnimationClock.getElapsedTime().asSeconds() > enemiesAnimationTimer)
    {
        enemiesAnimationClock.restart();
        animateAliens();
    }
    if (bulletsAnimationClock.getElapsedTime().asSeconds() > bulletsAnimationTimer)
    {
        bulletsAnimationClock.restart();
        animateBullets();
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

        if (!lockMovement)
        {
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

            if (gameState == "gameover")
            {

            }
        }

        window.clear();

        erasePlayerShots();
        level.draw();
        draw(dt);
        moveElements(dt);

        window.display();
    }
}

void Game::initGame()
{
    for (int i = 50; i <= 350; i = i + 70)
    {
        for (int j = 150; j < WINDOW_WIDTH - 150; j = j + 100)
        {
            GraphicalObject* enemy = new Enemy(&window, ALIENTEXTURE_MODEL_FILEPATH, ALIENTEXUTRE_2_MODEL_FILEPATH, sf::Vector2f(j, i));
            enemiesVec.push_back(enemy);
        }
    }
}

void Game::playerShots()
{
    GraphicalObject* bullet = new Bullet(&window, BULLET_FILEPATH, BULLET_LIGHT_FILEPATH, player->getRifleBound());
    playerBulletsVec.push_back(bullet);

    std::cout << "bulletsVec size: " << playerBulletsVec.size() << "\n";
}

void Game::erasePlayerShots()
{
    for (int i = 0; i < playerBulletsVec.size(); i++)
    {
        if (playerBulletsVec[i]->isOutOfBounds())
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
    // Bullet <=> Enemy
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

    // Bullet <=> Player
    for (int ie = 0; ie < enemyBulletsVec.size(); ie++)
    {
        if (player->collisionCheck(enemyBulletsVec[ie]))
        {
            enemyBulletsVec[ie]->draw();
            lockMovement = true;
            gameState = "gameover";
        }
    }

}

void Game::deleteDeadBodies()
{

}

void Game::animateAliens()
{
    for (auto& enemy : enemiesVec)
    {
        enemy->toggleTexture();
    }
}

void Game::animateBullets()
{
    //std::cout << "Change!\n";
    for (int i = 0; i < playerBulletsVec.size(); i++)
    {
        playerBulletsVec[i]->toggleTexture();
    }
}

void Game::alienShots()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<std::mt19937::result_type> distance(0, enemiesVec.size());
    GraphicalObject* randomAlien = enemiesVec[distance(gen)];

    // Alien shots
    if (enemyReloadClock.getElapsedTime().asSeconds() > enemyReloadTime)
    {
        GraphicalObject* bullet = new EnemyBullet(&window, ENEMYBULLET_FILEPATH, ENEMYBULLET_LIGHT_FILEPATH, randomAlien->getRifleBound());
        enemyBulletsVec.push_back(bullet);
        enemyReloadClock.restart();
    }
}
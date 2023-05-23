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

        level->draw();
        player->draw();
        drawWalls();
        drawEnemies();
        alienShots();
        checkCollisions();
    }
    else if (gameState == "gameover")
    {
        level->draw();
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
        level->moveBackgorund(dt, gameSpeed);
        for (auto& bullet : playerBulletsVec)
        {
            bullet->draw();
            bullet->moveEntity(dt);
        }
        for (auto& bullet : enemyBulletsVec)
        {
            bullet->draw();
            bullet->moveEntity(dt, gameSpeed);
        }

        for (auto& enemy : enemiesVec)
        {
            enemy->moveEntity(dt, gameSpeed);
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

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (gameState == "menu")
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                initGame();
                gameState = "game";
                lockMovement = false;
            }
        }
        else if (gameState == "game")
        {
            if (!lockMovement)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    player->moveEntityLeft(dt, 1);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    player->moveEntityRight(dt, 1);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    if (reloadClock.getElapsedTime().asSeconds() > reloadTime)
                    {
                        playerShots();
                        reloadClock.restart();
                    }
                }
            }
        }
        else if (gameState == "gameover")
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                eraseGame();
                initGame();
                gameState = "game";
                lockMovement = false;
                gameSpeed = 1.f;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                eraseGame();
                gameState = "menu";
                lockMovement = true;
            }
        }

        window.clear();

        eraseBullets();
        level->draw();
        draw(dt);
        moveElements(dt);

        window.display();
    }
}

void Game::initGame()
{
    // Create enemies
    for (int i = 50; i <= 350; i = i + 70)
    {
        for (int j = 0; j <= WINDOW_WIDTH - 350; j = j + 100)
        {
            Enemy* enemy = new Enemy(&window, ALIENTEXTURE_MODEL_FILEPATH, ALIENTEXUTRE_2_MODEL_FILEPATH, sf::Vector2f(j, i));
            enemiesVec.push_back(enemy);
        }
    }

    // Create walls
    Wall* wall1 = new Wall(&window, WALL_FULL_FILEPATH, sf::Vector2f(100.f, WINDOW_HEIGHT - 150.f));
    Wall* wall2 = new Wall(&window, WALL_FULL_FILEPATH, sf::Vector2f(375.f, WINDOW_HEIGHT - 150.f));
    Wall* wall3 = new Wall(&window, WALL_FULL_FILEPATH, sf::Vector2f(675.f, WINDOW_HEIGHT - 150.f));
    Wall* wall4 = new Wall(&window, WALL_FULL_FILEPATH, sf::Vector2f(950.f, WINDOW_HEIGHT - 150.f));
    wallsVec.push_back(wall1);
    wallsVec.push_back(wall2);
    wallsVec.push_back(wall3);
    wallsVec.push_back(wall4);
}

void Game::eraseGame()
{
    player->resetPosition();
    level->stopBackground();
    playerBulletsVec.clear();
    enemyBulletsVec.clear();
    enemiesVec.clear();
}

void Game::playerShots()
{
    Bullet* bullet = new Bullet(&window, BULLET_FILEPATH, BULLET_LIGHT_FILEPATH, player->getRifleBound());
    playerBulletsVec.push_back(bullet);

    //std::cout << "bulletsVec size: " << playerBulletsVec.size() << "\n";
}

void Game::eraseBullets()
{
    for (int i = 0; i < playerBulletsVec.size(); i++)
    {
        if (playerBulletsVec[i]->isOutOfBounds())
        {
            playerBulletsVec.erase(playerBulletsVec.begin() + i);
            //std::cout << "bulletsVec size: " << playerBulletsVec.size() << "\n";
            break;
        }
    }

    for (int i = 0; i < enemyBulletsVec.size(); i++)
    {
        if (enemyBulletsVec[i]->isOutOfBounds())
        {
            enemyBulletsVec.erase(enemyBulletsVec.begin() + i);
            //std::cout << "enemyBulletsVec size: " << enemyBulletsVec.size() << "\n";
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

void Game::drawWalls()
{
    for (auto& wall : wallsVec)
    {
        wall->draw();
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
                //std::cout << "enemiesVecSize: " << enemiesVec.size() << std::endl;
                playerBulletsVec.erase(playerBulletsVec.begin() + ib);
                enemiesVec.erase(enemiesVec.begin() + ie);

                // Speed up the game
                gameSpeed = gameSpeed * 1.05;
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

    //Bullet <=> Wall
    for (int iw = 0; iw < wallsVec.size(); iw++)
    {
        for (int ib = 0; ib < playerBulletsVec.size(); ib++)
        {
            if (wallsVec[iw]->collisionCheck(playerBulletsVec[ib]))
            {
                playerBulletsVec.erase(playerBulletsVec.begin() + ib);
                wallsVec[iw]->hit();
                wallsVec[iw]->changeTexture();
                if (wallsVec[iw]->getHP() == 0)
                {
                    wallsVec.erase(wallsVec.begin() + iw);
                }
            }
        }
        for (int ib = 0; ib < enemyBulletsVec.size(); ib++)
        {
            if (wallsVec[iw]->collisionCheck(enemyBulletsVec[ib]))
            {
                enemyBulletsVec.erase(enemyBulletsVec.begin() + ib);
                wallsVec[iw]->hit();
                wallsVec[iw]->changeTexture();
                if (wallsVec[iw]->getHP() == 0)
                {
                    wallsVec.erase(wallsVec.begin() + iw);
                }
            }
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
    for (int i = 0; i < playerBulletsVec.size(); i++)
    {
        playerBulletsVec[i]->toggleTexture();
    }
}

void Game::alienShots()
{
    if (enemiesVec.size() < 1)
    {
        return;
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<std::mt19937::result_type> distance(0, enemiesVec.size());
   Enemy* randomAlien = enemiesVec[distance(gen)];

    // Alien shots
    if (enemyReloadClock.getElapsedTime().asSeconds() > enemyReloadTime)
    {
        EnemyBullet* bullet = new EnemyBullet(&window, ENEMYBULLET_FILEPATH, ENEMYBULLET_LIGHT_FILEPATH, randomAlien->getRifleBound());
        enemyBulletsVec.push_back(bullet);
        enemyReloadClock.restart();
    }
}
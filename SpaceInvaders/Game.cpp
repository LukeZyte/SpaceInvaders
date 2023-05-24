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

void Game::draw(sf::Time& dt, sf::Clock gameTime)
{
    if (gameState == "menu")
    {
        mainMenu.draw();
        player->draw();
    }
    else if (gameState == "game")
    {
        clocksHandler();

        background->draw();
        safeAreaLine->draw();
        player->draw();
        drawWalls();
        drawEnemies();
        alienShots();
        checkCollisions(gameTime);
        checkAreaLine();
        topBoard.draw();
    }
    else if (gameState == "gameover")
    {
        background->draw();
        player->draw();
        drawEnemies();
        alienShots();
        checkCollisions(gameTime);
        gameover.draw();
    }
}

void Game::moveElements(sf::Time& dt)
{
    if (!lockMovement)
    {
        background->moveBackgorund(dt, gameSpeed);
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
    gameTime.restart();

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
            // Init game topboard values
            topBoard.setName(playerName);
            topBoard.setTimer(getGameTimeAsSec());

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
                gameSpeed = 1.f;
            }
        }

        window.clear();

        eraseBullets();
        background->draw();
        draw(dt, gameTime);
        moveElements(dt);

        window.display();
    }
}

void Game::initGame()
{
    resetScore();
    resetMaxCombo();
    resetCombo();
    topBoard.setScore(SCORE);
    gameTime.restart();
    enemyReloadClock.restart();

    // Create enemies
    for (int i = 100; i <= 400; i = i + 70)
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
    background->stopBackground();
    playerBulletsVec.clear();
    enemyBulletsVec.clear();
    enemiesVec.clear();
    wallsVec.clear();
}

void Game::playerShots()
{
    Bullet* bullet = new Bullet(&window, BULLET_FILEPATH, BULLET_LIGHT_FILEPATH, player->getRifleBound());
    playerBulletsVec.push_back(bullet);

    //std::cout << "bulletsVec size: " << playerBulletsVec.size() << "\n";
}

void Game::eraseBullets()
{
    // Player bullets
    for (int i = 0; i < playerBulletsVec.size(); i++)
    {
        if (playerBulletsVec[i]->isOutOfBounds())
        {
            playerBulletsVec.erase(playerBulletsVec.begin() + i);
            resetCombo();
            topBoard.setCombo(combo);
            //std::cout << "bulletsVec size: " << playerBulletsVec.size() << "\n";
            break;
        }
    }

    // Enemy bullets
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

void Game::checkCollisions(sf::Clock gameTime)
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
                gameSpeed = gameSpeed * 1.04;
                addToScore(pointsForKill, gameTime);
                topBoard.setScore(SCORE);
                addCombo();
                topBoard.setCombo(combo);
            }
        }
    }

    // Bullet <=> Player
    for (int ie = 0; ie < enemyBulletsVec.size(); ie++)
    {
        if (player->collisionCheck(enemyBulletsVec[ie]))
        {
            enemyBulletsVec[ie]->draw();
            death();
        }
    }

    //Bullet <=> Wall
    for (int iw = 0; iw < wallsVec.size(); iw++)
    {
        for (int ib = 0; ib < playerBulletsVec.size(); ib++)
        {
            if (wallsVec[iw]->collisionCheck(playerBulletsVec[ib]))
            {
                wallsVec[iw]->hit();
                wallsVec[iw]->changeTexture();
                playerBulletsVec.erase(playerBulletsVec.begin() + ib);
                if (wallsVec[iw]->getHP() == 0)
                {
                    wallsVec.erase(wallsVec.begin() + iw);
                }
                resetCombo();
                topBoard.setCombo(combo);
                removePoints(pointsForHittingWall);
                topBoard.setScore(SCORE);
            }
        }
        for (int ib = 0; ib < enemyBulletsVec.size(); ib++)
        {
            if (wallsVec[iw]->collisionCheck(enemyBulletsVec[ib]))
            {
                wallsVec[iw]->hit();
                wallsVec[iw]->changeTexture();
                enemyBulletsVec.erase(enemyBulletsVec.begin() + ib);
                if (wallsVec[iw]->getHP() == 0)
                {
                    wallsVec.erase(wallsVec.begin() + iw);
                }
            }
        }
    }
}

void Game::death()
{
    if (!lockMovement)
    {
        gameover.setValues(playerName, SCORE, maxCombo, getGameTimeAsSec());
    }
    lockMovement = true;
    gameState = "gameover";
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

void Game::checkAreaLine()
{
    for (auto& enemy : enemiesVec)
    {
        if (enemy->getYPos() > 850.f)
        {
            death();
            std::cout << "Passed the safe area line!\n";
        }
    }
}

void Game::addToScore(int value, sf::Clock gameTime)
{
    if (value > 0)
    {
        for (int i = 0; i < getGameTimeAsSec(); i = i + 3)  // -1 point every new 3s of the gameTime
        {
            value--;
        }
    }
    SCORE = SCORE + value + combo;
}

void Game::resetScore()
{
    SCORE = 0;
}

int Game::getGameTimeAsSec()
{
    return gameTime.getElapsedTime().asSeconds();
}

void Game::addCombo()
{
    combo = combo + 5;
    if (maxCombo < combo)
    {
        maxCombo = combo;
    }
}

void Game::resetCombo()
{
    combo = 0;
}

void Game::resetMaxCombo()
{
    maxCombo = 0;
}


void Game::removePoints(int value)
{
    SCORE = SCORE - value;
}
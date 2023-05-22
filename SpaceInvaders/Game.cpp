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
            bullet->draw();
            bullet->moveEntity(dt, true);
        }
        window.display();
    }
}

void Game::initGame()
{
    for (int i = 50; i <= 350; i = i + 70)
    {
        std::vector<GraphicalObject*> enemyLineVec;
        for (int j = 150; j < WINDOW_WIDTH - 150; j = j + 100)
        {
            GraphicalObject* enemy = new Enemy(&window, ALIENTEXTURE_MODEL_FILEPATH, ALIENTEXUTRE_2_MODEL_FILEPATH, sf::Vector2f(j, i));
            enemyLineVec.push_back(enemy);
        }
        enemiesVec.push_back(enemyLineVec);
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
    for (auto& enemyLineVec : enemiesVec)
    {
        for (auto& enemy : enemyLineVec)
        {
            enemy->draw();
        }
    }
}

void Game::checkCollisions()
{
    for (int iel = 0; iel < enemiesVec.size(); iel++)
    {
        for (int ie = 0; ie < enemiesVec[iel].size(); ie++)
        {
            for (int ib = 0; ib < playerBulletsVec.size(); ib++)
            {
                if (enemiesVec[iel][ie]->collisionCheck(playerBulletsVec[ib]))
                {
                    std::cout << "enemiesVecSize: " << enemiesVec[0].size() + enemiesVec[1].size() + enemiesVec[2].size() + enemiesVec[3].size() + enemiesVec[4].size() << std::endl;
                    playerBulletsVec.erase(playerBulletsVec.begin() + ib);
                    enemiesVec[iel].erase(enemiesVec[iel].begin() + ie);
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
    for (auto& enemyLineVec : enemiesVec)
    {
        for (auto& enemy : enemyLineVec)
        {
            enemy->toggleTexture();
        }
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
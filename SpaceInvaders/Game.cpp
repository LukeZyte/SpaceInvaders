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
    else if (gameState == "nickname")
    {
        nicknameScreen.draw();
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
        drawWalls();
        alienShots();
        checkCollisions(gameTime);
        gameover.draw();
    }
    else if (gameState == "win")
    {
        background->draw();
        player->draw();
        winScreen.draw();
    }
    else if (gameState == "records")
    {
        background->draw();
        player->draw();
        recordsScreen.draw();
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
    //sounds.playMainMusic();

    sf::Clock clock;
    gameTime.restart();
    bool lockKey = false;       // prevents spam at input field

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
                sounds.playClickSound();
                gameState = "nickname";
                nicknameScreen.resetNickname();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                sounds.playClickSound();
                getLastRecord(LAST_RECORD_FILEPATH);
                getRecord(RECORD_FILEPATH);

                if (lastNickname.size() < 3)
                {
                    recordsScreen.setUnavailableLastRecord();
                }
                else
                {
                    recordsScreen.setAvailableLastRecord();
                    recordsScreen.setLastValues(lastNickname, lastScore, lastMaxCombo, lastTime);
                }

                if (recordNickname.size() < 3)
                {
                    recordsScreen.setUnavailableBestRecord();
                }
                else
                {
                    recordsScreen.setAvailableBestRecord();
                    recordsScreen.setRecordValues(recordNickname, recordScore, recordMaxCombo, recordTime);
                }
                gameState = "records";
            }
        }
        else if (gameState == "records")
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                sounds.playClickSound();
                gameState = "menu";
            }
        }
        else if (gameState == "nickname")
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                if (nicknameScreen.getNickname().size() > 2)
                {
                    initGame();
                    gameState = "game";
                    setPlayerName(nicknameScreen.getNickname());
                    lockMovement = false;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                sounds.playClickSound();
                gameState = "menu";
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) && !lockKey)
            {
                lockMovement = true;
                nicknameScreen.updateNickname();
            }
            if (event.type == sf::Event::TextEntered && !lockKey && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                lockKey = true;
                nicknameScreen.updateNickname(event);
            }
            if (event.type == sf::Event::KeyReleased && lockKey)
            {
                lockKey = false;
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
                sounds.playClickSound();
                eraseGame();
                initGame();
                gameState = "game";
                lockMovement = false;
                gameSpeed = 1.f;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                sounds.playClickSound();
                eraseGame();
                gameState = "menu";
                lockMovement = true;
                gameSpeed = 1.f;
            }
        }
        else if (gameState == "win")
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                sounds.playClickSound();
                eraseGame();
                initGame();
                gameState = "game";
                lockMovement = false;
                gameSpeed = 1.f;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                sounds.playClickSound();
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
    player->resetHP();
    topBoard.setHP(player->getHP());
    resetScore();
    resetMaxCombo();
    resetCombo();
    topBoard.setScore(SCORE);
    gameTime.restart();
    enemyReloadClock.restart();
    winScreen.setNewRecord(false);

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
    Wall* wall2 = new Wall(&window, WALL_FULL_FILEPATH, sf::Vector2f(320.f, WINDOW_HEIGHT - 150.f));
    Wall* wall3 = new Wall(&window, WALL_FULL_FILEPATH, sf::Vector2f(563.f, WINDOW_HEIGHT - 150.f));
    Wall* wall4 = new Wall(&window, WALL_FULL_FILEPATH, sf::Vector2f(800.f, WINDOW_HEIGHT - 150.f));
    Wall* wall5 = new Wall(&window, WALL_FULL_FILEPATH, sf::Vector2f(1020.f, WINDOW_HEIGHT - 150.f));
    wallsVec.push_back(wall1);
    wallsVec.push_back(wall2);
    wallsVec.push_back(wall3);
    wallsVec.push_back(wall4);
    wallsVec.push_back(wall5);
}

void Game::eraseGame()
{
    player->resetPosition();
    background->stopBackground();
    playerBulletsVec.clear();
    enemyBulletsVec.clear();
    enemiesVec.clear();
    wallsVec.clear();
    resetMaxCombo();
    resetCombo();
    resetScore();
}

void Game::playerShots()
{
    Bullet* bullet = new Bullet(&window, BULLET_FILEPATH, BULLET_LIGHT_FILEPATH, player->getRifleBound());
    playerBulletsVec.push_back(bullet);
    sounds.playShootingSound();

    //std::cout << "bulletsVec size: " << playerBulletsVec.size() << "\n";
}

void Game::eraseBullets()
{
    // Player bullets
    for (int i = 0; i < std::ranges::size(playerBulletsVec); i++)
    {
        if (playerBulletsVec[i]->isOutOfBounds())
        {
            playerBulletsVec.erase(std::ranges::begin(playerBulletsVec) + i);
            resetCombo();
            topBoard.setCombo(combo);
            //std::cout << "bulletsVec size: " << playerBulletsVec.size() << "\n";
            break;
        }
    }

    // Enemy bullets
    for (int i = 0; i < std::ranges::size(enemyBulletsVec); i++)
    {
        if (enemyBulletsVec[i]->isOutOfBounds())
        {
            enemyBulletsVec.erase(std::ranges::begin(enemyBulletsVec) + i);
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
    for (int ie = 0; ie < std::ranges::size(enemiesVec); ie++)
    {
        for (int ib = 0; ib < std::ranges::size(playerBulletsVec); ib++)
        {
            if (enemiesVec[ie]->collisionCheck(playerBulletsVec[ib]))
            {
                sounds.playExplosionSound();
                //std::cout << "enemiesVecSize: " << enemiesVec.size() << std::endl;
                playerBulletsVec.erase(std::ranges::begin(playerBulletsVec) + ib);
                enemiesVec.erase(std::ranges::begin(enemiesVec) + ie);
                
                // Check if player won
                if (std::ranges::empty(enemiesVec))
                {
                    lockMovement = true;
                    gameState = "win";
                    winScreen.setValues(playerName, SCORE, maxCombo, getGameTimeAsSec());
                    sounds.playWinSound();

                    // Check if its a new record
                    getRecord(RECORD_FILEPATH);
                    if (SCORE > std::stoi(recordScore))
                    {
                        saveRecord(RECORD_FILEPATH);
                        winScreen.setNewRecord(true);
                    }
                    saveRecord(LAST_RECORD_FILEPATH);
                }

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
    for (int ie = 0; ie < std::ranges::size(enemyBulletsVec); ie++)
    {
        if (player->collisionCheck(enemyBulletsVec[ie]))
        {
            sounds.playWrongSound();
            player->removeHP(1);
            topBoard.setHP(player->getHP());
            removePoints(pointsForGettingHit);

            if (player->getHP() == 0)
            {
                enemyBulletsVec[ie]->draw();
                death();
            }

            enemyBulletsVec.erase(std::ranges::begin(enemyBulletsVec) + ie);
        }
    }

    //Bullet <=> Wall
    for (int iw = 0; iw < std::ranges::size(wallsVec); iw++)
    {
        for (int ib = 0; ib < std::ranges::size(playerBulletsVec); ib++)
        {
            if (wallsVec[iw]->collisionCheck(playerBulletsVec[ib]))
            {
                sounds.playWrongSound();
                wallsVec[iw]->destroy();
                playerBulletsVec.erase(std::ranges::begin(playerBulletsVec) + ib);
                if (wallsVec[iw]->getHP() == 0)
                {
                    wallsVec.erase(std::ranges::begin(wallsVec) + iw);
                }
                resetCombo();
                topBoard.setCombo(combo);
                //removePoints(pointsForHittingWall);
                topBoard.setScore(SCORE);
            }
        }
        for (int ib = 0; ib < std::ranges::size(enemyBulletsVec); ib++)
        {
            if (wallsVec[iw]->collisionCheck(enemyBulletsVec[ib]))
            {
                wallsVec[iw]->hit();
                wallsVec[iw]->changeTexture();
                enemyBulletsVec.erase(std::ranges::begin(enemyBulletsVec) + ib);
                if (wallsVec[iw]->getHP() == 0)
                {
                    wallsVec.erase(std::ranges::begin(wallsVec) + iw);
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
        saveRecord(LAST_RECORD_FILEPATH);
        sounds.playGameoverSound();
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
    for (int i = 0; i < std::ranges::size(playerBulletsVec); i++)
    {
        playerBulletsVec[i]->toggleTexture();
    }
}

void Game::alienShots()
{
    if (std::ranges::size(enemiesVec) < 1)
    {
        return;
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());

    // Alien shots
    if (enemyReloadClock.getElapsedTime().asSeconds() > enemyReloadTime)
    {
        std::uniform_int_distribution<std::mt19937::result_type> distance(0, std::ranges::size(enemiesVec));
        //Enemy* randomAlien = enemiesVec[distance(gen)];
        EnemyBullet* bullet = new EnemyBullet(&window, ENEMYBULLET_FILEPATH, ENEMYBULLET_LIGHT_FILEPATH, enemiesVec[distance(gen)]->getRifleBound());
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

void Game::setPlayerName(std::string nickname)
{
    playerName = nickname;
}

void Game::saveRecord(std::string recordFilepath)
{
    std::ofstream file;
    file.open(recordFilepath);
    if (file.is_open())
    {
        file << playerName << "\n";
        file << SCORE << "\n";
        file << maxCombo << "\n";
        file << getGameTimeAsSec() << "\n";
        file.close();
    }
    else
    {
        std::cout << "Could not open the file!\n";
    }
    std::cout << "New record saved into " << recordFilepath << "!\n";
}

void Game::getRecord(std::string recordFilepath)
{
    std::ifstream file(recordFilepath);

    std::filesystem::path filepath = recordFilepath;
    if (!std::filesystem::is_regular_file(recordFilepath))
    {
        std::cout << "File with record does not exists!\n";
    }

    if (file.is_open())
    {
        std::getline(file, recordNickname, '\n');
        std::getline(file, recordScore, '\n');
        std::getline(file, recordMaxCombo, '\n');
        std::getline(file, recordTime, '\n');
        file.close();
    }
    else
    {
        std::cout << "Could not read best record from the file!\n";
    }
    std::cout << "Record retrieved from " << recordFilepath << "!\n";
}

void Game::getLastRecord(std::string recordFilepath)
{
    std::ifstream file(recordFilepath);

    std::filesystem::path filepath = recordFilepath;
    if (!std::filesystem::is_regular_file(recordFilepath))
    {
        std::cout << "File with last record does not exists!\n";
    }

    if (file.is_open())
    {
        std::getline(file, lastNickname, '\n');
        std::getline(file, lastScore, '\n');
        std::getline(file, lastMaxCombo, '\n');
        std::getline(file, lastTime, '\n');
        file.close();
    }
    else
    {
        std::cout << "Could not read last record from the file!\n";
    }
    std::cout << "Last record retrieved from " << recordFilepath << "!\n";
}
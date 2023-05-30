#pragma once

//#include "Globals.h"
import Globals;
#include "MainMenu.h"
#include "Player.h"
#include "GraphicalObject.h"
#include "Background.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Gameover.h"
#include "Wall.h"
#include "SafeArea.h"
#include "TopBoard.h"
#include "WinScreen.h"
#include "NicknameScreen.h"
#include "RecordsScreen.h"
#include "Sounds.h"

#include <algorithm>
#include <random>
#include <iterator>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <ranges>
#include <fstream>
#include <filesystem>

class Game
{
public:
	Game(sf::RenderWindow& _window);
	~Game();

	void gameLoop();
	void draw(sf::Time& dt, sf::Clock gameTime);

private:
	// Vectors
	std::vector<Bullet*> playerBulletsVec;			// all player's bullets on screen
	std::vector<EnemyBullet*> enemyBulletsVec;		// all enemy's bullets on screen
	std::vector<Enemy*> enemiesVec;					// all enemies on screen
	std::vector<Wall*> wallsVec;					// all walls on screen

	// Methods
	void initGame();
	void eraseGame();
	void clocksHandler();

	void playerShots();
	void alienShots();
	void eraseBullets();
	void drawEnemies();
	void drawWalls();
	void checkCollisions(sf::Clock gameTime);
	void death();
	void moveElements(sf::Time& dt);
	void checkAreaLine();					// have any enemy passed the safe area line

	void animateAliens();
	void animateBullets();

	void addToScore(int vlaue, sf::Clock gameTime);
	void resetScore();
	void addCombo();
	void resetCombo();
	void resetMaxCombo();
	void removePoints(int value);

	int getGameTimeAsSec();
	void setPlayerName(std::string nickname);

	// Saving data
	void saveRecord(std::string recordFilepath);
	void getRecord(std::string recordFilepath);
	void getLastRecord(std::string recordFilepath);

	// Inits
	sf::RenderWindow& window;
	Sounds sounds;
	MainMenu mainMenu{ window };
	Gameover gameover{ window };
	TopBoard topBoard{ window };
	WinScreen winScreen{ window };
	RecordsScreen recordsScreen{ window };
	NicknameScreen nicknameScreen{ window };
	Player* player = new Player(&window, PLAYER_MODEL_FILEPATH, sf::Vector2f(WINDOW_WIDTH / 2 - 30.f, WINDOW_HEIGHT - 70.f));
	Background* background = new Background(window);
	SafeArea* safeAreaLine = new SafeArea(&window, SAFEAREA_FILEPATH, sf::Vector2f(0.f, 840.f));

	// States and Vars
	std::string gameState;
	bool lockMovement = true;
	float gameSpeed = 1;
	std::string playerName = "PLAYER";

	// Points system
	int SCORE = 0;
	int combo = 0;
	int maxCombo = 0;
	int pointsForKill = 50;
	int pointsForHittingWall = 100;

	std::string lastNickname = "";
	std::string lastScore = "0";
	std::string lastMaxCombo = "0";
	std::string lastTime = "0";

	std::string recordNickname = "";
	std::string recordScore = "0";
	std::string recordMaxCombo = "0";
	std::string recordTime = "0";

	// Utils
	sf::Clock reloadClock;
	float reloadTime = 0.5;
	sf::Clock enemyReloadClock;
	float enemyReloadTime = 0.8;
	sf::Clock enemyDeathAnimationClock;
	sf::Clock enemiesAnimationClock;
	float enemiesAnimationTimer = 0.6;
	sf::Clock bulletsAnimationClock;
	float bulletsAnimationTimer = 0.05;
	sf::Clock gameTime;
};


#pragma once

#include "Globals.h"
#include "MainMenu.h"
#include "Player.h"
#include "GraphicalObject.h"
#include "Level.h"
#include "Bullet.h"
#include "Enemy.h"

#include <algorithm>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game(sf::RenderWindow& _window);
	~Game();

	void gameLoop();
	void draw(sf::Time& dt);

private:
	// Vectors
	std::vector<GraphicalObject*> playerBulletsVec;		// all player's bullets on screen
	std::vector<GraphicalObject*> enemyBulletsVec;		// all enemy's bullets on screen
	std::vector<std::vector<GraphicalObject*>> enemiesVec;	// all enemies on screen

	// Methods
	void initGame();

	void playerShots();
	void erasePlayerShots();
	void drawEnemies();
	void checkCollisions();
	void deleteDeadBodies();		// removes objects that have deadAnimation

	void clocksHandler();
	void animateAliens();
	void animateBullets();

	// Inits
	sf::RenderWindow& window;
	MainMenu mainMenu{ window };
	
	GraphicalObject* player = new Player(&window, PLAYER_MODEL_FILEPATH, sf::Vector2f(WINDOW_WIDTH / 2 - 30.f, WINDOW_HEIGHT - 100.f));
	Level level{ window };

	// States
	std::string gameState;

	// Utils
	sf::Clock reloadClock;
	float reloadTime = 0.5;
	sf::Clock enemyDeathAnimationClock;
	sf::Clock enemiesAnimationClock;
	float enemiesAnimationTimer = 0.6;
	sf::Clock bulletsAnimationClock;
	float bulletsAnimationTimer = 0.05;
};


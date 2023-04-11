#pragma once

#include "Globals.h"
#include "MainMenu.h"
#include "Player.h"
#include "Level.h"
#include "Bullet.h"

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
	void draw();

private:
	// Vectors
	std::vector<Bullet> playerBulletsVec;	// all player's bullets on screen
	std::vector<Bullet> enemyBulletsVec;	// all enemy's bullets on screen

	// Methods
	void playerShots();
	void erasePlayerShots();

	// Inits
	sf::RenderWindow& window;
	MainMenu mainMenu{ window };
	Player player{ &window, PLAYER_MODEL_FILEPATH, sf::Vector2f(WINDOW_WIDTH / 2 - 30.f, WINDOW_HEIGHT - 60.f) };
	Level level{ window };

	// States
	std::string gameState;

	// Utils
	sf::Clock reloadClock;
	float reloadTime = 0.5;
};


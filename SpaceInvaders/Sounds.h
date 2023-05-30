#pragma once

import Globals;

#include <iostream>
#include <SFML/Audio.hpp>

class Sounds
{
public:
	Sounds();
	~Sounds();

	void playClickSound() { click.play(); }
	void playExplosionSound() { explosion.play(); }
	void playGameoverSound() { gameover.play(); }
	void playShootingSound() { shooting.play(); }
	void playWinSound() { win.play(); }
	void playWrongSound() { wrong.play(); }
	void playMainMusic() { mainMusic.play(); }

private:
	sf::SoundBuffer clickBuff;
	sf::SoundBuffer shootingBuff;
	sf::SoundBuffer explosionBuff;
	sf::SoundBuffer gameoverBuff;
	sf::SoundBuffer winBuff;
	sf::SoundBuffer wrongBuff;

	sf::Sound click;
	sf::Sound shooting;
	sf::Sound explosion;
	sf::Sound gameover;
	sf::Sound win;
	sf::Sound wrong;

	sf::Music mainMusic;
};


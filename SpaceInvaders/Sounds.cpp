#include "Sounds.h"

Sounds::Sounds()
{
	// Sounds Init
	if (!clickBuff.loadFromFile(CLICK_SOUND_FILEPATH))
	{
		std::cout << "Could not load a sound file!\n";
	}
	if (!explosionBuff.loadFromFile(EXPLOSION_SOUND_FILEPATH))
	{
		std::cout << "Could not load a sound file!\n";
	}
	if (!gameoverBuff.loadFromFile(GAMEOVER_SOUND_FILEPATH))
	{
		std::cout << "Could not load a sound file!\n";
	}
	if (!shootingBuff.loadFromFile(SHOOTING_SOUND_FILEPATH))
	{
		std::cout << "Could not load a sound file!\n";
	}
	if (!winBuff.loadFromFile(WIN_SOUND_FILEPATH))
	{
		std::cout << "Could not load a sound file!\n";
	}
	if (!wrongBuff.loadFromFile(WRONG_SOUND_FILEPATH))
	{
		std::cout << "Could not load a sound file!\n";
	}

	// Musics Init
	/*if (!mainMusic.openFromFile(MAIN_MUSIC_FILEPATH))
	{
		std::cout << "Could not load a music file!\n";
	}*/

	click.setBuffer(clickBuff);
	explosion.setBuffer(explosionBuff);
	gameover.setBuffer(gameoverBuff);
	shooting.setBuffer(shootingBuff);
	win.setBuffer(winBuff);
	wrong.setBuffer(wrongBuff);
}

Sounds::~Sounds()
{

}
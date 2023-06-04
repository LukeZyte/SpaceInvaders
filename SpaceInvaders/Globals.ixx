#include <string>

export module Globals;

export
{
	// Main
	int WINDOW_WIDTH = 1200;
	int WINDOW_HEIGHT = 1000;
	size_t FPS_LIMIT = 120;
	std::string RECORD_FILEPATH = "saves\\record.txt";
	std::string LAST_RECORD_FILEPATH = "saves\\lastRecord.txt";

	// Fonts
	std::string PIXELOIDSANS_FILEPATH = "resources/font/PixeloidSans.ttf";
	std::string PRESSSTART2P_FILEPATH = "resources/font/PressStart2P.ttf";

	// Textures
	std::string SPACE_BACKGROUND_FILEPATH = "resources/img/space_bg.jpg";
	std::string PLAYER_MODEL_FILEPATH = "resources/img/PlayerTexture.png";
	std::string BULLET_FILEPATH = "resources/img/bullet.png";
	std::string BULLET_LIGHT_FILEPATH = "resources/img/bullet_light.png";
	std::string ALIENTEXTURE_MODEL_FILEPATH = "resources/img/AlienTexture.png";
	std::string ALIENTEXUTRE_2_MODEL_FILEPATH = "resources/img/AlienTexture2.png";
	std::string ENEMYBULLET_FILEPATH = "resources/img/enemyBullet.png";
	std::string ENEMYBULLET_LIGHT_FILEPATH = "resources/img/enemyBullet2.png";
	std::string WALL_FULL_FILEPATH = "resources/img/wall_full.png";
	std::string WALL_4_FILEPATH = "resources/img/wall_4.png";
	std::string WALL_3_FILEPATH = "resources/img/wall_3.png";
	std::string WALL_2_FILEPATH = "resources/img/wall_2.png";
	std::string WALL_1_FILEPATH = "resources/img/wall_1.png";
	std::string SAFEAREA_FILEPATH = "resources/img/safearea.png";
	std::string HP_FILEPATH = "resources/img/hp.png";

	// Sounds
	std::string CLICK_SOUND_FILEPATH = "resources/sounds/click.wav";
	std::string EXPLOSION_SOUND_FILEPATH = "resources/sounds/explosion.wav";
	std::string GAMEOVER_SOUND_FILEPATH = "resources/sounds/gameover.wav";
	std::string SHOOTING_SOUND_FILEPATH = "resources/sounds/shooting.wav";
	std::string WIN_SOUND_FILEPATH = "resources/sounds/win.wav";
	std::string WRONG_SOUND_FILEPATH = "resources/sounds/wrong.wav";

	// Music
	//std::string MAIN_MUSIC_FILEPATH = "resources/sounds/Her-Heart.ogg";
}
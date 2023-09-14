#pragma once
#include "Boss.h"
#include "player.h"
#include "bullet.h"
#include "Enemy.h"
#include <map>
#include <sstream>
#include <SFML/Audio.hpp>
#include <cmath>
class game
{
private:
	sf::RenderWindow* window;

	// resources
	std::map<std::string, sf::Texture*> textures;
	std::map<int, sf::Texture*> enemyTexture;
	std::vector<bullet*> bullets;

	player* Player;
	std::vector<Enemy*> enemies;
	float spawnTimer,spawnTimerMax;

	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	// gui
	sf::Font font;
	sf::Text text;
	sf::Text gameOverText;

	// world
	sf::Sprite worldBackground;
	sf::Texture backgroundTexture;

	// system
	unsigned points;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::SoundBuffer explosion;
	sf::Sound soundExplosion;
	void initSounds();

	sf::Sprite inimigo;

	Boss* boss;
	float spawnBossTimer;
	bool bossAlive = false;
	bool bossAconteceu = false;

	void updateGui();
	void renderGui();
	void initGui();
	void initWindow();
	void initPlayer();
	void initBoss();
	void initEnemies();
	void initTextures();
	void initVariables();
	void initWorld();
public:
	game();
	virtual ~game();

	// Funcs
	void run();
	void update();
	void render();
	void renderWorld();
	void updateWorld();
	void pollEvents();
	void pollEventsPlayer();
	void updateBullets();
	void updateEnemies();
	void updateCollision();
	void updateCombat();
	void bossCombat();


};


#pragma once
#include "player.h"
#include "bullet.h"
#include "Enemy.h"
#include <map>
#include <sstream>
class game
{
private:
	sf::RenderWindow* window;

	// resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<bullet*> bullets;

	player* Player;
	std::vector<Enemy*> enemies;
	float spawnTimer,spawnTimerMax;

	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	// gui
	sf::Font font;
	sf::Text text;

	// world
	sf::Sprite worldBackground;
	sf::Texture backgroundTexture;

	// system
	unsigned points;


	void updateGui();
	void renderGui();
	void initGui();
	void initWindow();
	void initPlayer();
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


};


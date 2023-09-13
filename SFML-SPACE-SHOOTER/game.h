#pragma once
#include "player.h"
#include "bullet.h"
#include <map>
class game
{
private:
	sf::RenderWindow* window;

	// resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<bullet*> bullets;

	player* Player;

	void initWindow();
	void initPlayer();
	void initTextures();
	void initVariables();
public:
	game();
	virtual ~game();

	// Funcs
	void run();
	void update();
	void render();
	void pollEvents();
	void pollEventsPlayer();
	void updateBullets();

};


#pragma once
#include <SFML/Graphics.hpp>
class Enemy
{
private:
	sf::CircleShape shape;
	int hp;
	int hpMax;
	int damage;
	int points;
	int type;

	void initShape();
	void initVariables();
public:
	Enemy(float posX, float posY);
	virtual ~Enemy();

	void update();
	void render(sf::RenderTarget* target);
};


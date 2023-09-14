#pragma once
#include <SFML/Graphics.hpp>
class Enemy
{
private:
	std::map<int, sf::Texture*> enemyTexture;
	sf::Sprite shape;
	unsigned pointCount;
	int speed;
	int hp;
	int hpMax;
	int damage;
	int type;
	int points;
	void initVariables();

	void initShape();
public:
	Enemy(float posX, float posY);
	virtual ~Enemy();

	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	void update();
	void render(sf::RenderTarget* target);
};


#pragma once
#include <SFML/Graphics.hpp>
class Boss
{
private:
	sf::Texture texture;
	sf::Sprite spite;
	
public:
	Boss();
	virtual ~Boss();
	int speed;
	int hp;
	int hpMax;
	int damage;
	bool ocorreu = false;
	bool alive = false;
	const sf::FloatRect getBounds() const;
	void update();
	void render(sf::RenderTarget& target);
	void initVariables();
	void initSprite();
	void morte();
	const sf::Texture* getTexure() const;
	void setTexture();
};


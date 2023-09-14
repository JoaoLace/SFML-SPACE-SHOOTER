#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
class player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float moveSpeed;
	float attackCooldown;
	float attackCooldownMax;


	void initTexture();
	void initSprite();
	void initVaribles();

	int hp;
	int hpMax;
public:
	player();
	virtual ~player();

	// acessors
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getGlobalBouncePlayer() const;
	const int& getHp() const;
	const int& getHpMax() const;

	// modificar
	void setPosition(float pos_x, float pos_y);
	void setHp(const int hp);
	void loseHp(const float value);

	int points;
	void move(const float dirX, float dirY);
	void update();
	void updateAttack();
	const bool canAttack();
	void render(sf::RenderTarget& target);
};


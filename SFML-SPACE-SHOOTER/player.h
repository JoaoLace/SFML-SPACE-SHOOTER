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
public:
	player();
	virtual ~player();

	// acessors
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getGlobalBouncePlayer() const;

	void move(const float dirX, float dirY);
	void update();
	void updateAttack();
	const bool canAttack();
	void render(sf::RenderTarget& target);
};


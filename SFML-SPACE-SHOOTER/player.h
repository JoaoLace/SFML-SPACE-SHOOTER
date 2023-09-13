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

	void initTexture();
	void initSprite();
public:
	player();
	virtual ~player();

	// acessors
	const sf::Vector2f& getPos() const;

	void move(const float dirX, float dirY);
	void update();
	void render(sf::RenderTarget& target);
};


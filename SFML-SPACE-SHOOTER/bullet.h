#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class bullet
{
private:
	sf::Sprite shape;

	// IMPORTANT!!!! CREATE TEXTURE TO BULLET AS A POINTER !!!

	sf::Vector2f direction;
	float moveSpeed;

	void initSprite();
	void initTexture();
public:
	bullet();
	bullet(sf::Texture * texture, float pos_x, float pos_y, float dir_x, float dir_y, float move_speed);
	virtual ~bullet();

	// acessors
	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget* target);
};


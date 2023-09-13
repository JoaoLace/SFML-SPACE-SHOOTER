#include "player.h"

void player::initTexture()
{ 
	//"C:\Users\lacer\OneDrive\Área de Trabalho\repos\SFML-SPACE-SHOOTER\SFML-SPACE-SHOOTER\Files\ship.png"
	texture.loadFromFile("Files/ship.png");
	
}

void player::initSprite()
{
	sprite.setTexture(texture);
	sprite.scale(0.2f, 0.2f);
}
const sf::Vector2f& player::getPos() const
{
	return sprite.getPosition();
}
void player::move(const float dirX, float dirY)
{
	sprite.move(moveSpeed * dirX, moveSpeed * dirY);
}
void player::update()
{
}
player::player()
{

	moveSpeed = 2.f;
	initTexture();
	initSprite();
}
player::~player()
{
}
void player::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}

// Funcs 

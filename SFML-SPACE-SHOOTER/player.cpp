#include "player.h"

void player::initTexture()
{ 
	//"C:\Users\lacer\OneDrive\�rea de Trabalho\repos\SFML-SPACE-SHOOTER\SFML-SPACE-SHOOTER\Files\ship.png"
	texture.loadFromFile("Files/ship.png");
	
}

void player::initSprite()
{
	sprite.setTexture(texture);
	sprite.scale(0.2f, 0.2f);
}
void player::initVaribles()
{
	moveSpeed = 2.f;
	attackCooldownMax = 10.f;
	attackCooldown = attackCooldownMax;
}
const sf::Vector2f& player::getPos() const
{
	return sprite.getPosition();
}
const sf::FloatRect player::getGlobalBouncePlayer() const
{
	return sprite.getGlobalBounds();
}
void player::move(const float dirX, float dirY)
{
	sprite.move(moveSpeed * dirX, moveSpeed * dirY);
}
void player::update()
{
	updateAttack();
}
void player::updateAttack()
{
	if (attackCooldown < attackCooldownMax)
	{
		attackCooldown += 0.5f;
	}
	
}
const bool player::canAttack()
{
	if (attackCooldown >= attackCooldownMax)
	{
		attackCooldown = 0.f;
		return true;
	}
	return false;
}
player::player()
{
	initVaribles();
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

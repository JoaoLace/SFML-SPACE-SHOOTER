#include "Enemy.h"

void Enemy::initShape()
{
	shape.setRadius(rand() % 20 + 20);
	shape.setPointCount(static_cast<size_t>(rand() % 20) + 3);
	shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

void Enemy::initVariables()
{
	this->hpMax = 10;
	this->hp = hpMax;
	this->damage = 1;
	this->points = 5;
	this->type = 0;
}

Enemy::Enemy(float posX,float posY)
{
	initShape();
	initVariables();
	shape.setPosition(posX, posY);
	
}

Enemy::~Enemy()
{
}

void Enemy::update()
{
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(shape);
}

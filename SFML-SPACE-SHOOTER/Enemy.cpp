#include "Enemy.h"

void Enemy::initShape()
{
	shape.setRadius(pointCount * 5);
	shape.setPointCount(pointCount);
	shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

void Enemy::initVariables()
{
	pointCount = (rand() % 8 + 3);
	speed = static_cast<float>(pointCount/2);
	hpMax = static_cast<int>(pointCount);
	hp = hpMax;
	damage = 1;
	type = 0;
	points = pointCount;
}

Enemy::Enemy(float posX,float posY)
{
	initVariables();
	initShape();
	shape.setPosition(posX, posY);
	
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return points;
}

const int& Enemy::getDamage() const
{
	return damage;
}

void Enemy::update()
{
	shape.move(0.f, speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(shape);
}

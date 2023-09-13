#include "bullet.h"

void bullet::initSprite()
{
}

void bullet::initTexture()
{
}

bullet::bullet()
{
}

bullet::bullet(sf::Texture * texture, float pos_x, float pos_y, float dir_x, float dir_y, float move_speed)
{
	shape.scale(sf::Vector2f(0.05f, 0.05f));
	shape.setTexture(*texture);
	shape.setPosition(pos_x, pos_y);
	direction.x = dir_x;
	direction.y = dir_y;
	moveSpeed = move_speed;
}

bullet::~bullet()
{
}

const sf::FloatRect bullet::getBounds() const
{
	return shape.getGlobalBounds();
}

void bullet::update()
{
	shape.move(moveSpeed * direction);
}

void bullet::render(sf::RenderTarget* target)
{
	target->draw(shape);
}

#include "Boss.h"

Boss::Boss()
{
	initSprite();
	initVariables();
}

Boss::~Boss()
{
}

const sf::FloatRect Boss::getBounds() const
{
	return spite.getGlobalBounds();
}

void Boss::update()
{
	if (alive)
	spite.move(0.f, 0.5f);
}

void Boss::render(sf::RenderTarget& target)
{
	if (alive)
	target.draw(spite);
}

void Boss::initVariables()
{
	speed = 2;
	hpMax = 20;
	hp = hpMax;
}

void Boss::initSprite()
{

	texture.loadFromFile("Files/boss.png");
	spite.setTexture(texture);
	spite.setPosition(300.f, -10.f);
}

void Boss::morte()
{
}
const sf::Texture* Boss::getTexure() const
{
	
	return spite.getTexture();
}

void Boss::setTexture()
{
	spite.setColor(sf::Color(255,255,255,0));
}


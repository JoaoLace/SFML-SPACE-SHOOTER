#include "game.h"
// Private funcs
void game::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Space Shooter", sf::Style::Close | sf::Style::Titlebar);
	window->setFramerateLimit(144);
	window->setVerticalSyncEnabled(false);
}

void game::initPlayer()
{
	Player = new player();
}

void game::initTextures()
{
	textures["BULLET"] = new sf::Texture();
	textures["BULLET"]->loadFromFile("Files/bullet.png");
}

// Con/des
game::game()
{
	initWindow();
	initTextures();
	initPlayer();

	
}

game::~game()
{
	delete window;
	delete Player;
	
	for (auto& var : textures)
	{
		delete var.second;
	}

	for (auto* var : bullets)
	{
		delete var;
	}
}

// Functions
void game::run()
{
	while (window->isOpen())
	{
		update();
		render();
	}
}

void game::update()
{
	pollEvents();
	pollEventsPlayer();
	updateBullets();
}

void game::render()
{
	window->clear();
	Player->render(*window);
	
	
	for (auto* bullet : bullets)
	{
		bullet->render(window);
	}
	window->display();
}

void game::pollEvents()
{
	sf::Event e;
	while (window->pollEvent(e))
	{
		switch (e.Event::type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (e.Event::key.code == sf::Keyboard::Escape)
				window->close();
				break;
		default:
			break;
		}
	}
}

void game::pollEventsPlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		Player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		Player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		Player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		Player->move(0.f, 1.f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		bullets.push_back(new bullet
		(textures["BULLET"],Player->getPos().x, Player->getPos().y, 0.f, 0.f, 0.f));
	}
}

void game::updateBullets()
{
	for (auto* bullet : bullets)
	{
		bullet->update();
	}
}
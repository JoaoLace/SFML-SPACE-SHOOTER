#include "game.h"
void game::updateGui()
{
	std::stringstream ss;
	ss << "SCORE: " << points;
	text.setString(ss.str());

	Player->setHp(100);
	float hpPercent = static_cast<float>(Player->getHp()) / Player->getHpMax();
	playerHpBar.setSize(sf::Vector2f(200.f * hpPercent, playerHpBar.getSize().y));

}
void game::renderGui()
{
	window->draw(text);
	window->draw(playerHpBarBack);
	window->draw(playerHpBar);
}
void game::initGui()
{
	font.loadFromFile("Files/PixelEmulator-xq08.ttf");
	text.setFont(font);
	text.setCharacterSize(22);
	text.setPosition(5.f, 0.f);
	text.setFillColor(sf::Color::White);
	text.setString("teset");

	playerHpBar.setSize(sf::Vector2f(200.f, 20.f));
	playerHpBar.setFillColor(sf::Color::Red);
	playerHpBar.setPosition(sf::Vector2f(5.f, 40.f));

	playerHpBarBack = playerHpBar;
	playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

}
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

void game::initEnemies()
{
	spawnTimerMax = 50.f;
	spawnTimer = spawnTimerMax;
}

void game::initTextures()
{
	textures["BULLET"] = new sf::Texture();
	textures["BULLET"]->loadFromFile("Files/bullet.png");
}

void game::initVariables()
{
	points = 0;
}

void game::initWorld()
{
	// "C:\Users\lacer\OneDrive\Área de Trabalho\repos\SFML-SPACE-SHOOTER\SFML-SPACE-SHOOTER\Files\fundo.jpg"
	backgroundTexture.loadFromFile("Files/fundo.jpg");
	worldBackground.setTexture(backgroundTexture);
}

// Con/des
game::game()
{
	initWindow();
	initGui();
	initTextures();
	initVariables();
	initPlayer();
	initEnemies();
	initWorld();
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

	for (auto* e : enemies)
	{
		delete e;
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
	Player->update();
	updateCollision();
	updateBullets();
	updateEnemies();
	updateCombat();
	updateGui();
	updateWorld();

}

void game::render()
{
	window->clear();
	renderWorld();
	Player->render(*window);
	
	
	for (auto* bullet : bullets)
	{
		bullet->render(window);
	}
	for (auto* e : enemies)
	{
		e->render(window);
	}
	renderGui();
	window->display();
}

void game::renderWorld()
{
	window->draw(worldBackground);
}

void game::updateWorld()
{
}

void game::updateCollision()
{
	// esquerda
	if (Player->getGlobalBouncePlayer().left < 0.f)
	{
		Player->setPosition(0.f, Player->getGlobalBouncePlayer().top);
	}

	// direita
	if (Player->getGlobalBouncePlayer().left > window->getSize().x - Player->getGlobalBouncePlayer().width)
	{
		Player->setPosition(window->getSize().x - Player->getGlobalBouncePlayer().width, Player->getGlobalBouncePlayer().top);
	}

	// cima
	if (Player->getGlobalBouncePlayer().top < 0.f)
	{
		Player->setPosition(Player->getGlobalBouncePlayer().left, 0);
	}

	// baixo
	if (Player->getGlobalBouncePlayer().top > window->getSize().y - Player->getGlobalBouncePlayer().height)
	{
		Player->setPosition(Player->getGlobalBouncePlayer().left, window->getSize().y - Player->getGlobalBouncePlayer().height);
	}
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && Player->canAttack() == true)
	{
		bullets.push_back(new bullet
		(textures["BULLET"],Player->getPos().x + (Player->getGlobalBouncePlayer().width/2 - 12.6f)
						   ,Player->getPos().y - (Player->getGlobalBouncePlayer().height/2)
						   ,0.f, -1.f, 5.f));
	}
}

void game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : bullets)
	{
		bullet->update();

		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			delete bullets.at(counter);
			bullets.erase(bullets.begin() + counter);
			--counter;
		}
	}
	++counter;
}

void game::updateEnemies()
{
	
	spawnTimer += 0.5f;
	if (spawnTimer >= spawnTimerMax)
	{
		enemies.push_back(new Enemy(rand() % window->getSize().x - 20.f, -100.f));
		spawnTimer = 0.f;
	}

	unsigned counter = 0;
	for (auto* enemy : enemies)
	{
		enemy->update();

		if (enemy->getBounds().top + enemy->getBounds().height > window->getSize().y)
		{
			delete enemies.at(counter);
			enemies.erase(enemies.begin() + counter);
			--counter;
		}
		else if (enemy->getBounds().intersects(Player->getGlobalBouncePlayer()))
		{
			Player->loseHp(enemies.at(counter)->getDamage());
			delete enemies.at(counter);
			enemies.erase(enemies.begin() + counter);
			--counter;
			
		}

		 ++counter;
	}
}

void game::updateCombat()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		bool enemy_deleted = false;
		for (int k = 0; k < bullets.size() && enemy_deleted == false; k++)
		{
			if (enemies[i]->getBounds().intersects(bullets[k]->getBounds()))
			{
				points += enemies[i]->getPoints();
				delete	enemies[i];
				enemies.erase(enemies.begin() + i);

				delete	bullets[k];
				bullets.erase(bullets.begin() + k);

				
				enemy_deleted = true;
			}
		}
	}
}


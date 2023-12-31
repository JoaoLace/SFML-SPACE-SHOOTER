#include "game.h"
void game::initSounds()
{
	// "C:\Users\lacer\OneDrive\�rea de Trabalho\repos\SFML-SPACE-SHOOTER\SFML-SPACE-SHOOTER\Files\gun.wav"
	// "C:\Users\lacer\OneDrive\�rea de Trabalho\repos\SFML-SPACE-SHOOTER\SFML-SPACE-SHOOTER\Files\sample.wav"
	buffer.loadFromFile("Files/gun.wav");
	sound.setBuffer(buffer);
	sound.setVolume(20);

	explosion.loadFromFile("Files/explodeSound.wav");
	soundExplosion.setBuffer(explosion);
	soundExplosion.setVolume(30);
}
void game::updateGui()
{
	std::stringstream ss;
	ss << "SCORE: " << points;
	text.setString(ss.str());

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


	gameOverText.setFont(font);
	gameOverText.setCharacterSize(60);
	gameOverText.setPosition(200.f, 300.f);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setString("GAME OVER");

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

void game::initBoss()
{
	boss = new Boss();
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
	spawnBossTimer = 100;
}

void game::initWorld()
{
	// "C:\Users\lacer\OneDrive\�rea de Trabalho\repos\SFML-SPACE-SHOOTER\SFML-SPACE-SHOOTER\Files\fundo.jpg"
	backgroundTexture.loadFromFile("Files/fundo.jpg");
	worldBackground.setTexture(backgroundTexture);
}

// Con/des
game::game()
{
	initWindow();
	initGui();
	initSounds();
	initTextures();
	initVariables();
	initPlayer();
	initBoss();
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
		pollEvents();
		
		if (Player->getHp() > 0)
		update();

		render();
	}
}

void game::update()
{
	pollEventsPlayer();
	Player->update();
	updateCollision();
	updateBullets();
	updateEnemies();
	updateCombat();
	updateGui();
	updateWorld();
	if (points > 100 && !bossAconteceu)
	{
		bossAlive = true;
		boss->alive = true;
		bossCombat();	
		boss->update();
			
	}
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

	if (Player->getHp() <= 0)
	{
		window->draw(gameOverText);
	}

	if (bossAlive == true)
	{
		boss->render(*window);
	}

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
		sound.play();
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

		if (enemy->getBounds().top  > window->getSize().y)
		{
			delete enemies.at(counter);
			enemies.erase(enemies.begin() + counter);

		}
		else if (enemy->getBounds().intersects(Player->getGlobalBouncePlayer()))
		{
			Player->loseHp(enemies.at(counter)->getDamage());
			delete enemies.at(counter);
			enemies.erase(enemies.begin() + counter);
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
				enemies[i]->setSprite("Files/explode.png");

				points += enemies[i]->getPoints();
				
				soundExplosion.play();
				enemy_deleted = true;
			}
			if (enemy_deleted)
			{
				delete	enemies[i];
				enemies.erase(enemies.begin() + i);
				i--;
				delete	bullets[k];
				bullets.erase(bullets.begin() + k);
				
			}
			
		}
	}
}

void game::bossCombat()
{
	for (int k = 0; k < bullets.size() && boss->alive == true; k++)
	{
		if (boss->getBounds().intersects(bullets[k]->getBounds()))
		{
			delete	bullets[k];
			bullets.erase(bullets.begin() + k);
			boss->hp--;
			
		}
		/*if (bullets[k]->getBounds().top + bullets[k]->getBounds().height < 0.f)
			{
				delete bullets.at(k);
				bullets.erase(bullets.begin() + k);
			}*/
	}
	if (boss->hp <= 0)
	{
		boss->alive = false;
		//delete boss;
		//boss = nullptr;
		bossAconteceu = true;
		boss->setTexture();
		points += 50;
		soundExplosion.play();
	}

	if (boss->getBounds().intersects(Player->getGlobalBouncePlayer()))
	{
		Player->loseHp(100);
	}
}
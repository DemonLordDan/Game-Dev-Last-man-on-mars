/*
Title: Game Class
Description: This class handles all main functions of the game, bringing all the classes functionality to one place.
Author: Andrew Morrison
*/
#include "Game.h"
#include "menu.h"

/*
#########################
### Private Functions ###
#########################
*/
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(this->windowWidth, this->windowHeight), "Last Man on Mars", sf::Style::Close | sf::Style::Titlebar);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("res/textures/bullet.png");
}

void Game::initGUI()
{
	// Load font
	if  (!this->font.loadFromFile("res/fonts/Pixellari.ttf"))
	{
		std::cout << "ERROR::GAME::Failed to load font" << "\n";
	}

	// Init point text
	this->pointText.setPosition(20.f, 60.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("Test");

	// Init Gameover Text
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(100);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f, 
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	// Init Player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

	// Wave Number GUI
	this->waveNumberText.setFont(this->font);
	this->waveNumberText.setCharacterSize(100);
	this->waveNumberText.setFillColor(sf::Color::Red);
	this->waveNumberText.setString("1");
	this->waveNumberText.setPosition(20, (this->windowHeight - 60) - waveNumberText.getGlobalBounds().height);

	// Shop GUI Text
	this->shopText.setFont(this->font);
	this->shopText.setCharacterSize(100);
	this->shopText.setFillColor(sf::Color::Yellow);
	this->shopText.setString("Shop");
	this->shopText.setPosition(
		this->window->getSize().x / 2.f - this->shopText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 3.f - this->shopText.getGlobalBounds().height / 2.f);

	// Shop Upgrade DMG
	this->upgradeDmgText.setFont(this->font);
	this->upgradeDmgText.setCharacterSize(50);
	this->upgradeDmgText.setFillColor(sf::Color::White);
	this->upgradeDmgText.setString("Upgrade Damage");
	this->upgradeDmgText.setPosition(
		this->window->getSize().x / 3.f - this->upgradeDmgText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->upgradeDmgText.getGlobalBounds().height / 2.f);

	// Shop Upgrade DMG
	this->upgradeFirerateText.setFont(this->font);
	this->upgradeFirerateText.setCharacterSize(50);
	this->upgradeFirerateText.setFillColor(sf::Color::White);
	this->upgradeFirerateText.setString("Upgrade Firerate");
	this->upgradeFirerateText.setPosition(
		(this->window->getSize().x / 3.f) * 2 - this->upgradeFirerateText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->upgradeFirerateText.getGlobalBounds().height / 2.f);

	// Shop Upgrade Damage Button
	this->upgradeDmgButton.setSize(sf::Vector2f(upgradeDmgText.getGlobalBounds().width, upgradeDmgText.getGlobalBounds().height));
	this->upgradeDmgButton.setFillColor(sf::Color(25, 25, 25, 200));
	this->upgradeDmgButton.setPosition(upgradeDmgText.getPosition());

	// Shop Upgrade Firerate Button
	this->upgradeFirerateButton.setSize(sf::Vector2f(upgradeFirerateText.getGlobalBounds().width, upgradeFirerateText.getGlobalBounds().height));
	this->upgradeFirerateButton.setFillColor(sf::Color(25, 25, 25, 200));
	this->upgradeFirerateButton.setPosition(upgradeFirerateText.getPosition());

	this->shopOpen = false;
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("res/textures/background.png"))
	{
		std::cout << "ERROR::GAME::Could not load background texture." << "\n";
	}

	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initSystems()
{
	this->points = 0;
	this->waveNumber = 1;
}

void Game::initPlayer()
{
	this->player = new Player(this->windowWidth/2, this->windowHeight/2);
}

void Game::initEnemies()
{
	this->spawnTimerMax = 5.f;
	this->spawnTimer = this->spawnTimerMax;
	this->spawnTimerRate = 3.f;
	this->maxEnemies = 24;

	this->enemiesPerRound = 10;
	this->enemiesLeft = enemiesPerRound;

	this->enemySpeed = 10.f;
}

void Game::sMenu() {
	menu Menu;
	while (Menu.running()) {
		Menu.update();
		Menu.render();
		
		if (Menu.getSNumber() == 1) {
			return;
		}
		else if (Menu.getSNumber() == 5) {
			gameState = -1;
			return;
		}
	}
	if (!Menu.running()) {
		gameState = -1;
	}
}

void Game::prewarm() {
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initSystems();

	this->initPlayer();
	this->initEnemies();
}
/*
###################
### Constructor ###
###################
*/
Game::Game()
{
	this->sMenu();
	this->prewarm();
	
	
}

/*
#####################
### Deconstructor ###
#####################
*/
Game::~Game()
{
	if (this->window != NULL) {
		delete this->window;
		delete this->player;

		// Delete Textures
		for (auto& i : this->textures)
		{
			delete i.second;
		}

		// Delete Bullets
		for (auto* i : this->bullets)
		{
			delete i;
		}

		// Delete Enemies
		for (auto* i : this->enemies)
		{
			delete i;
		}
	}
	
	exit;
}

/*
#################
### Functions ###
#################
*/
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();

		if (this->player->getHp() > 0 && this->shopOpen == false)
		{
			this->update();
		}
		else if (this->shopOpen)
		{
			this->updateShop();
		}

		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;

	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}
		if (gameState == -1) {
			this->window->close();
		}
	}
}

void Game::updateMousePosition()
{
	// Collects the current mouse position
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateInput(float dt)
{
	// Move Player
	// Move Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->player->move(-1.f, 0.f, dt);
	}
	// Move Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->player->move(1.f, 0.f, dt);
	}
	// Move Up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->player->move(0.f, -1.f, dt);
	}
	// Move Down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->player->move(0.f, 1.f, dt);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		updateMousePosition();

		// Collect the center position of the player
		this->playerCenter = sf::Vector2f(this->player->getPos().x + (this->player->getBounds().width/2.f), this->player->getPos().y + (this->player->getBounds().height / 2.f));

		// Calculates the normalised aim direction
		this->aimDir = this->mousePosView - this->playerCenter;
		this->aimDirNorm = this->aimDir / static_cast<float>(sqrt(pow(this->aimDir.x, 2) + pow(this->aimDir.y, 2)));

		// Creates a new bullet
		this->bullets.push_back(new Bullet(
			this->textures["BULLET"],
			this->playerCenter.x,
			this->playerCenter.y,
			this->aimDirNorm, 400.f
		));
	}
}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "Points: " << this->points;

	this->pointText.setString(ss.str());

	// Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));

	// Update Wave GUI
	std::stringstream waveNo;

	waveNo << this->waveNumber;

	this->waveNumberText.setString(waveNo.str());
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	// Left world collision
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	// Right world collision
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	// Top world collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	// Bottom world collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updateBullets(float dt)
{
	unsigned counter = 0;

	for (auto *bullet : this->bullets)
	{
		bullet->update(dt);

		// Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			// Delete the bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;

			std::cout << this->bullets.size() << "\n";
		}
		// Bullet culling (right of screen)
		else if (bullet->getBounds().left + bullet->getBounds().width > this->windowWidth)
		{
			// Delete the bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;

			std::cout << this->bullets.size() << "\n";
		}
		// Bullet culling (bottom of screen)
		else if (bullet->getBounds().top + bullet->getBounds().height > this->windowHeight)
		{
			// Delete the bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;

			std::cout << this->bullets.size() << "\n";
		}
		// Bullet culling (left of screen)
		else if (bullet->getBounds().left + bullet->getBounds().width < 0.f)
		{
			// Delete the bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;

			std::cout << this->bullets.size() << "\n";
		}

		++counter;
	}
}

void Game::updateEnemies(float dt)
{
	// Checks to see if there are enemies left for this round
	if (this->enemiesLeft > 0)
	{
		// Checks if the spawn cap has been met
		if (this->enemies.size() <= this->maxEnemies)
		{
			// Variables (these will decide if the enemy will spawn at the top/bottom/left/right of the screen)
			int enemy_x = rand() % 2 + 1;
			int enemy_y = rand() % 2 + 1;

			// Final spawn position coordinates
			int pos_x = 0;
			int pos_y = 0;

			// Define spawn coordinates
			if (enemy_x == 1)
			{
				if (enemy_y == 1)
				{
					pos_x = 40;
					pos_y = rand() % (windowHeight - 40) + 40;
				}
				else
				{
					pos_x = rand() % (windowWidth - 40) + 40;
					pos_y = 40;
				}
			}
			else
			{
				if (enemy_y == 1)
				{
					pos_x = (windowWidth - 80);
					pos_y = rand() % (windowHeight - 80) + 40;
				}
				else
				{
					pos_x = rand() % (windowWidth - 80) + 40;
					pos_y = (windowHeight - 80);
				}
			}


			// Increase the spawn timer
			this->spawnTimer += (this->spawnTimerRate * dt);

			if (this->spawnTimer >= this->spawnTimerMax)
			{
				if (this->waveNumber <= 10)
				{
					// Spawn the enemy
					this->enemies.push_back(new Enemy(
						pos_x, pos_y, // set enemy position
						this->enemySpeed + this->waveNumber)); // set enemy movement speed (10 + <waveNumber>)
				}
				// Ensures the maximum movement speed is double the original
				else
				{
					// Spawn the enemy
					this->enemies.push_back(new Enemy(pos_x, pos_y, this->enemySpeed * 2));
				}

				// Reset the spawn timer
				this->spawnTimer = 0.f;
				// Update the spawn cap
				--this->enemiesLeft;
			}
		}
	}
	// Update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update(dt, this->player->getPos());

		// If the enemy collides with the player
		if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			// Remove Hp from the user
			this->player->loseHp(this->enemies.at(counter)->getDamage());

			// Remove enemies
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);

			--counter;
		}

		++counter;
	}
}

void Game::updateCombat(float dt)
{
	// Loop through all the enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool enemy_removed = false;
		// Update all the enemies
		this->enemies[i]->update(dt, this->player->getPos());

		// Loop through all active bullets
		for (size_t k = 0; k < this->bullets.size() && !enemy_removed; k++)
		{
			// If an enemy and a bullet collide
			if (this->bullets[k]->getBounds().intersects(this->enemies[i]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();

				// Remove enemies
				this->enemies[i]->loseHp(this->player->getDamage());
				if (this->enemies[i]->getHp() == 0)
				{
					delete this->enemies[i];
					this->enemies.erase(this->enemies.begin() + i);
				}

				// Remove bullets
				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				// Confirm that an enemy was removed
				enemy_removed = true;
			}
		}
	}
}

void Game::updatePlayer(float dt)
{
	this->player->update(dt);
}

void Game::updateWave()
{
	// Start next wave
	if (this->enemies.size() == 0 && this->enemiesLeft == 0)
	{
		// Increase wave number
		this->waveNumber++;
		// Increment number of enemies
		this->enemiesLeft = this->enemiesPerRound * this->waveNumber;

		// Update spawn timer rate 
		if (this->waveNumber < 5)
		{
			this->spawnTimerRate = 2.f;
		}
		else if (this->waveNumber < 10)
		{
			this->spawnTimerRate = 3.f;
		}
		else if (this->waveNumber < 15)
		{
			this->spawnTimerRate = 4.f;
		}
		else if (this->waveNumber < 20)
		{
			this->spawnTimerRate = 5.f;
		}

		// End of wave shop
		this->shopOpen = true;
	}
}

void Game::updateShop()
{
	// Update the mouse position
	updateMousePosition();

	// If the mouse hovers over the upgrade button
	if (this->upgradeDmgButton.getGlobalBounds().contains(this->mousePosView))
	{
		// Update colour
		this->upgradeDmgButton.setFillColor(sf::Color(25, 25, 25, 200));

		// Upgrade damage 
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->player->setDamage(player->getDamage() + 10);
			this->shopOpen = false;
		}
	}
	else
	{
		// Return the colour to normal
		this->upgradeDmgButton.setFillColor(sf::Color(50, 50, 50, 200));
	}

	// If the mouse hovers over the upgrade button
	if (this->upgradeFirerateButton.getGlobalBounds().contains(this->mousePosView))
	{
		// Update colour
		this->upgradeFirerateButton.setFillColor(sf::Color(25, 25, 25, 200));

		// Upgrade firerate
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->player->setCooldownMultiplier(player->getAttackCooldownMax() + 1.f);
			this->shopOpen = false;
		}
	}
	else
	{
		this->upgradeFirerateButton.setFillColor(sf::Color(50, 50, 50, 200));
	}

}

void Game::update()
{
	// Reset clock, recalculate deltatime
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();

	this->updateInput(dt);

	this->updatePlayer(dt);
	this->updateCollision();
	this->updateBullets(dt);
	this->updateEnemies(dt);
	this->updateCombat(dt);

	this->updateGUI();
	this->updateWorld();
	this->updateWave();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);

	// Player GUI
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);

	// Wave Number
	this->window->draw(this->waveNumberText);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::renderShop()
{
	// Render shop buttons
	this->window->draw(this->upgradeDmgButton);
	this->window->draw(this->upgradeFirerateButton);
	this->window->draw(this->exitShop);

	// Render shop Text
	this->window->draw(this->shopText);
	this->window->draw(this->upgradeDmgText);
	this->window->draw(this->upgradeFirerateText);
}

void Game::render()
{
	// Clear the window to allow drawing everything else.
	this->window->clear();

	// Draw World (background)
	this->renderWorld();

	// Draw player
	this->player->render(*this->window);
	
	// Draw bullets
	for (auto *bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	// Render the enemies
	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	// Render the GUI
	this->renderGUI();

	// Render the shop
	if (this->shopOpen)
	{
		this->renderShop();
	}

	// Game over screen
	if (this->player->getHp() <= 0)
	{
		this->window->draw(this->gameOverText);
	}

	// Display the current Frame
	this->window->display();
}

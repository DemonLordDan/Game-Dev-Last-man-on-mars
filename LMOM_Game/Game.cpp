#pragma once
#include "Game.h"

// Private Functions
void Game::initVariables()
{
	this->window = nullptr;

	// Game Logic
	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Last Man on Mars", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(144);
}

void Game::initEnemies()
{
	// Initialize enemy properties
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(50.f, 50.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Red);
	//this->enemy.setOutlineColor(sf::Color::White);
	//this->enemy.setOutlineThickness(2.f);
}

// Constructors / Deconstructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

// Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

// Functions
void Game::spawnEnemy()
{
	/*
		@return void

		Spawns enemies and sets their colour / positions.
		- Sets a random position
		- Sets a random colour
		- Adds enemy to the vector
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y));

	this->enemy.setFillColor(sf::Color::Red);

	// Spawn the enemy
	this->enemies.push_back(this->enemy);
}

void Game::pollEvents()
{
	// Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		}
	}
}

void Game::updateMousePositions()
{
	/*
		@ return void

		Updates the mouse positions:
		- Mouse position relative to window (Vector2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
	/*
		@return void

		Update the enemy spawn timer and spawns enemies
		when the total amount of enemies is smaller than the maximum.
		- Moves the enemies.
		- Removes the enemies at the edge of the screen. // TODO
	*/

	// Updating the timer for enemy Spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			// Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}

	// Moves the enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		// Boolean to check if the enemy was deleted
		bool deleted = false;

		this->enemies[i].move(-1.f,1.f);

		// Check if clicked upon
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
			{
				deleted = true;
			}
		}

		// If the enemy is past the bottom of the screen
		if (this->enemies[i].getPosition().y > this->window->getSize().y || this->enemies[i].getPosition().y < 0 || this->enemies[i].getPosition().x > this->window->getSize().x || this->enemies[i].getPosition().x < 0)
		{
			deleted = true;
		}

		// Final Delete (remove enemy)
		if (deleted)
		{
			this->enemies.erase(this->enemies.begin() + i);
		}
	}

}

void Game::update()
{
	this->pollEvents();
	
	this->updateMousePositions();

	this->updateEnemies();
}

void Game::renderEnemies()
{
	// Rendering all the enemies
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Game::render()
{
	/*
		Description: Renders the game objects
		- clear old frame
		- render objects
		- display frame in window
	*/

	// Clear the previous frame
	this->window->clear();

	// Draw game objects
	this->renderEnemies();

	// Display
	this->window->display();
}

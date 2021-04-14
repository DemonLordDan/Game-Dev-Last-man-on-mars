#include "Game.h""

// Private Functions
void Game::initVariables()
{
	this->window = nullptr;
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

void Game::update()
{
	this->pollEvents();

	// Update mouse position
	// Relative to the screen
	//std::cout << "Mouse pos: " << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << "\n";
	// Relative to the window
	//std::cout << "Mouse pos: " 
		//<< sf::Mouse::getPosition(*this->window).x << " " 
		//<< sf::Mouse::getPosition(*this->window).y << "\n";
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
	this->window->draw(this->enemy);

	// Display
	this->window->display();
}

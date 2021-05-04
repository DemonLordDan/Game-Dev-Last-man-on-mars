/*
Title: MainMenu Class
Description: This is the Main Menu of the game, this is the first object that will be presented to the user.
Author: Andrew Morrison
*/
#include "MainMenu.h"

/*
#########################
### Private Functions ###
#########################
*/
void MainMenu::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(this->windowWidth, this->windowHeight), "Last Man on Mars", sf::Style::Close | sf::Style::Titlebar);
	this->window->setVerticalSyncEnabled(false);
}

void MainMenu::initVariables()
{
	finalOutput = 0;
}

void MainMenu::initGUI()
{
	// Load font
	if (!this->font.loadFromFile("res/fonts/Pixellari.ttf"))
	{
		std::cout << "ERROR::GAME::Failed to load font" << "\n";
	}

	// Init Title Text
	this->titleText.setFont(this->font);
	this->titleText.setCharacterSize(100);
	this->titleText.setFillColor(sf::Color::White);
	this->titleText.setString("Last Man on Mars");
	this->titleText.setPosition((
		this->window->getSize().x / 2) - this->titleText.getGlobalBounds().width / 2,
		this->window->getSize().y * 0.1);

	// Init Start Button
	this->startText.setFont(this->font);
	this->startText.setCharacterSize(50);
	this->startText.setFillColor(sf::Color::White);
	this->startText.setString("START");
	this->startText.setPosition((
		this->window->getSize().x / 2) - this->startText.getGlobalBounds().width / 2,
		this->window->getSize().y * 0.4);

	// Init Leaderboard Button
	this->leaderboardText.setFont(this->font);
	this->leaderboardText.setCharacterSize(50);
	this->leaderboardText.setFillColor(sf::Color::White);
	this->leaderboardText.setString("LEADERBOARD");
	this->leaderboardText.setPosition((
		this->window->getSize().x / 2) - this->leaderboardText.getGlobalBounds().width / 2,
		this->window->getSize().y * 0.6);

	// Init Quit Button
	this->quitText.setFont(this->font);
	this->quitText.setCharacterSize(50);
	this->quitText.setFillColor(sf::Color::White);
	this->quitText.setString("QUIT");
	this->quitText.setPosition((
		this->window->getSize().x / 2) - this->quitText.getGlobalBounds().width / 2,
		this->window->getSize().y * 0.8);
}

/*
###################
### Constructor ###
###################
*/
MainMenu::MainMenu()
{
	initWindow();
	initGUI();
}

/*
#####################
### Deconstructor ###
#####################
*/
MainMenu::~MainMenu()
{

}

/*
#################
### Functions ###
#################
*/
int MainMenu::run()
{
	initVariables();

	while (this->window->isOpen() && this->finalOutput == 0)
	{
		this->updatePollEvents();

		this->update();

		this->render();
	}

	return finalOutput;
}

void MainMenu::close()
{
	this->window->close();
}

void MainMenu::updatePollEvents()
{
	sf::Event e;

	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
		{
			this->window->close();
			this->finalOutput = 3;
		}
	}
}

void MainMenu::updateMousePosition()
{
	// Collects the current mouse position
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}


void MainMenu::updateGUI()
{
	// If the mouse hovers over the start button
	if (this->startText.getGlobalBounds().contains(this->mousePosView))
	{
		// Update colour
		this->startText.setFillColor(sf::Color::Yellow);

		// Update output
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->finalOutput = 1;
		}
	}
	else
	{
		// Return the colour to normal
		this->startText.setFillColor(sf::Color::White);
	}

	// If the mouse hovers over the leaderboard button
	if (this->leaderboardText.getGlobalBounds().contains(this->mousePosView))
	{
		// Update colour
		this->leaderboardText.setFillColor(sf::Color::Yellow);

		// Update output
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->finalOutput = 2;
		}
	}
	else
	{
		// Return the colour to normal
		this->leaderboardText.setFillColor(sf::Color::White);
	}

	// If the mouse hovers over the quit button
	if (this->quitText.getGlobalBounds().contains(this->mousePosView))
	{
		// Update colour
		this->quitText.setFillColor(sf::Color::Yellow);

		// Update output
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->finalOutput = 3;
		}
	}
	else
	{
		// Return the colour to normal
		this->quitText.setFillColor(sf::Color::White);
	}
}

void MainMenu::update()
{
	updateMousePosition();
	updateGUI();
}

void MainMenu::renderGUI()
{
	this->window->draw(this->titleText);
	this->window->draw(this->startText);
	this->window->draw(this->leaderboardText);
	this->window->draw(this->quitText);
}

void MainMenu::render()
{
	// Clear the window to allow drawing everything else.
	this->window->clear();

	renderGUI();

	// Display the current Frame
	this->window->display();
}

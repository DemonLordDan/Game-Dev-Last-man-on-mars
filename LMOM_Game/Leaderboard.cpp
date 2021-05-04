/*
Title: LeaderBoard Class
Description: This will handle the leaderboard window which will show the top 5 scores of the game.
Author: Andrew Morrison
*/
#include "Leaderboard.h"

/*
#########################
### Private Functions ###
#########################
*/
void Leaderboard::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(this->windowWidth, this->windowHeight), "Last Man on Mars", sf::Style::Close | sf::Style::Titlebar);
	this->window->setVerticalSyncEnabled(false);
}

void Leaderboard::initGUI()
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
	this->titleText.setString("LEADERBOARD");
	this->titleText.setPosition((
		this->window->getSize().x / 2) - this->titleText.getGlobalBounds().width / 2,
		this->window->getSize().y * 0.1);

	// Init Labels Text
	this->labels.setFont(this->font);
	this->labels.setCharacterSize(50);
	this->labels.setFillColor(sf::Color::White);
	this->labels.setString("WAVE   -   POINTS");
	this->labels.setPosition((
		this->window->getSize().x / 2) - this->labels.getGlobalBounds().width / 2,
		this->window->getSize().y * 0.25);

	// Init High Scores
	this->scores.setFont(this->font);
	this->scores.setCharacterSize(50);
	this->scores.setFillColor(sf::Color::White);
	this->scores.setPosition((
		this->window->getSize().x / 2) - this->scores.getGlobalBounds().width / 2,
		this->window->getSize().y * 0.3);

	// Init Back Button
	this->backText.setFont(this->font);
	this->backText.setCharacterSize(50);
	this->backText.setFillColor(sf::Color::White);
	this->backText.setString("BACK");
	this->backText.setPosition(
		60.f,
		this->window->getSize().y * 0.8);
}

void Leaderboard::readFromFile()
{
	// Read the file
	ifstream file("res/saves/leaderboard.txt");

	// Validation
	if (!file.is_open())
	{
		cout << "ERROR::LEADERBOARD::Failed to load leaderboard.txt" << "\n";
	}

	// Temporary Variables
	string tempString;

	// Using a while loop along with getline(), read through the file, line by line
	while (getline(file, this->fileData))
	{
		stringstream ss(this->fileData);

		getline(ss, tempString, ',');
		this->waveNumber = stoi(tempString);

		getline(ss, tempString, ',');
		this->points = stoi(tempString);

		addToScores();
	}

	// Close the file
	file.close();
}

void Leaderboard::addToScores()
{
	this->scores.setString(
		scores.getString() + "\n" + 
		to_string(this->waveNumber) + " - " + 
		to_string(this->points)
	);
}

/*
###################
### Constructor ###
###################
*/
Leaderboard::Leaderboard()
{
	initWindow();
	readFromFile();
	initGUI();
}

/*
#####################
### Deconstructor ###
#####################
*/
Leaderboard::~Leaderboard()
{

}

/*
#################
### Functions ###
#################
*/
void Leaderboard::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();

		this->update();

		this->render();
	}
}

void Leaderboard::close()
{
	this->window->close();
}

void Leaderboard::updatePollEvents()
{
	sf::Event e;

	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
		{
			this->window->close();
		}
	}
}

void Leaderboard::updateMousePosition()
{
	// Collects the current mouse position
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}


void Leaderboard::updateGUI()
{
	// If the mouse hovers over the back button
	if (this->backText.getGlobalBounds().contains(this->mousePosView))
	{
		// Update colour
		this->backText.setFillColor(sf::Color::Yellow);

		// Update output
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->window->close();
		}
	}
	else
	{
		// Return the colour to normal
		this->backText.setFillColor(sf::Color::White);
	}
}

void Leaderboard::update()
{
	updateMousePosition();
	updateGUI();
}

void Leaderboard::renderGUI()
{
	this->window->draw(this->titleText);
	this->window->draw(this->labels);
	this->window->draw(this->scores);
	this->window->draw(this->backText);
}

void Leaderboard::render()
{
	// Clear the window to allow drawing everything else.
	this->window->clear();

	renderGUI();

	// Display the current Frame
	this->window->display();
}

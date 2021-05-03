#pragma once

#include "menu.h"

void menu::initVariables()
{
	this->window = nullptr;
	this->screenNumber = 2;
	if (!font.loadFromFile("res/fonts/Pixellari.ttf")) {
		this->window->close();
	};
}

void menu::renderButtons() {
	for (auto& e : this->buttons)
	{
		this->window->draw(e);
	}
	for (auto& e : this->msgs)
	{
		this->window->draw(e);
	}
};

void menu::render()
{
	/*
		Description: Renders the game objects
		- clear old frame
		- render objects
		- display frame in window
	*/


	// Clear the previous frame
	this->window->clear();
	
	// Rendering all the buttons
	this->renderButtons();

	// Display
	this->window->display();
}



void menu::pollEvents()
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
		if (screenNumber == 5) {
			this->window->close();
		}
	}
}

menu::~menu()
{
	delete this->window;
}

void menu::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Last Man on Mars", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(144);
}

const bool menu::running() const
{
	return this->window->isOpen();
}

void menu::ScreenSwapper()
{
	
}

void menu::initButtons() {
	this->button.setPosition(-100.f, -100.f);
	this->button.setSize(sf::Vector2f(200.f, 100.f));
	this->button.setScale(sf::Vector2f(1.f, 1.f));
	this->button.setFillColor(sf::Color::Black);
	
}

void menu::buttonPosition() {
	this->buttons.empty();
	if (screenNumber == 0) {
		for (int i = 0; i < 5; i++) {
			this->button.setPosition(static_cast<float>(this->window->getSize().x) / static_cast<float>(2), 50 + static_cast<float>((this->window->getSize().y)/static_cast<float>(5))*i);
			this->button.setFillColor(sf::Color::Black);
			this->buttons.push_back(this->button);
		}

		std::string text = "START";
		
		sf::Text standIn;
		standIn.setColor(sf::Color::Black);
		standIn.setFont(font);
		standIn.setString(text);
		standIn.setColor(sf::Color::White);
		standIn.setStyle(sf::Text::Regular);
		msgs.push_back(standIn);
		msgs[0].setPosition(this->buttons[0].getPosition());
		text = "Info";
		standIn.setString(text);
		msgs.push_back(standIn);
		msgs[1].setPosition(this->buttons[1].getPosition());
		text = "Controls";
		standIn.setString(text);
		msgs.push_back(standIn);
		msgs[2].setPosition(this->buttons[2].getPosition());
		text = "Credits";
		standIn.setString(text);
		msgs.push_back(standIn);
		msgs[3].setPosition(this->buttons[3].getPosition());
		text = "Exit";
		standIn.setString(text);
		msgs.push_back(standIn);
		msgs[4].setPosition(this->buttons[4].getPosition());

	} else if (screenNumber == 2) {
		
		this->button.setPosition(static_cast<float>(this->window->getSize().x) + static_cast<float>(200), static_cast<float>((this->window->getSize().y) - static_cast<float>(100)));
		this->button.setFillColor(sf::Color::Black);
		this->buttons.push_back(this->button);
		
		std::string text = "Return";

		sf::Text standIn;
		standIn.setColor(sf::Color::White);
		standIn.setFont(font);
		standIn.setString(text);
		standIn.setStyle(sf::Text::Regular);
		msgs.push_back(standIn);
		msgs[0].setPosition(this->buttons[0].getPosition());
	}
	
}

menu::menu()
{
	this->initVariables();
	this->initWindow();
	this->initButtons();
	this->buttonPosition();
}

void menu::update() {
	this->pollEvents();
	this->updateMousePositions();

	for (int i = 0; i < 5; i++) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->buttons[i].getGlobalBounds().contains(this->mousePosView))
			{
				this->screenNumber = i + 1;
				
			}
			this->buttonPosition();
		}
	}
}

void menu::updateMousePositions()
{
	/*
		@ return void

		Updates the mouse positions:
		- Mouse position relative to window (Vector2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

}
int menu::getSNumber() {
	return screenNumber;
}
void menu::setSNumber(int number) {
	screenNumber = number;
}
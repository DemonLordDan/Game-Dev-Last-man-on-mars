#include "menu.h"

void menu::initVariables()
{
	this->window = nullptr;

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
	this->button.setPosition(10.f, 10.f);
	this->button.setSize(sf::Vector2f(50.f, 50.f));
	this->button.setScale(sf::Vector2f(5.f, 1.f));
	this->button.setFillColor(sf::Color::White);
}

void menu::buttonPosition() {
	if (screenNumber == 0) {
		for (int i = 0; i < 5; i++) {
			this->buttons.push_back(this->button);
			this->buttons[i].setPosition((this->window->getSize().x) / static_cast<float>(2), 100 + ((this->window->getSize().y)/static_cast<float>(5))*i);
		}
		std::string text = "START";
		std::vector<sf::Text> msgs;
		msgs[0].setString(text);
		msgs[0].setPosition(this->buttons[0].getPosition());
		text = "Info";
		msgs[1].setString(text);
		msgs[1].setPosition(this->buttons[1].getPosition());
		text = "Controls";
		msgs[2].setString(text);
		msgs[2].setPosition(this->buttons[2].getPosition());
		text = "Credits";
		msgs[3].setString(text);
		msgs[3].setPosition(this->buttons[3].getPosition());
		text = "Exit";
		msgs[4].setString(text);
		msgs[4].setPosition(this->buttons[4].getPosition());

	}
}

void menu::update() {
	for (int i = 0; i < 4; i++) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->buttons[i].getGlobalBounds().contains(this->mousePosView))
			{
				this->screenNumber = i + 1;
			}
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
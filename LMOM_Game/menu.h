#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class menu {
private:

	//Private Variables
	sf::Font font;
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	std::vector<sf::RectangleShape> buttons;
	sf::RectangleShape button;
	std::vector<sf::Text> msgs;

	//Private Functions
	void initVariables();
	void initWindow();
	void ScreenSwapper();
	void initButtons();
	void buttonPosition();

public:
	//Public Variables
	int screenNumber;
	
	//Accessors
	const bool running() const;

	//Constructors and Deconstructors
	menu();
	virtual ~menu();

	//Functions
	void pollEvents();
	void updateMousePositions();
	int getSNumber();
	void setSNumber(int number);
	void update();
	void renderButtons();
	void render();
};
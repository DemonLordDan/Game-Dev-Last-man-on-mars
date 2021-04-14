#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
	Description: This class is acting as the Game Engine.
*/

class Game
{
private:
	// Variables
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	// Game Objects
	sf::RectangleShape enemy;

	// Private Functions
	void initVariables();
	void initWindow();
	void initEnemies();

public:
	// Constructors & Destructors
	Game();
	virtual ~Game();

	// Accessors
	const bool running() const;

	// Functions
	void pollEvents();
	void update();
	void render();
};
/*
Title: MainMenu Header
Description: Creates all the required variables, functions, accessors and modifiers for the MainMenu class.
Author: Andrew Morrison
*/
#pragma once

#include<SFML/Graphics.hpp>
#include<map>
#include<string>
#include<sstream>
#include<iostream>

class MainMenu
{
private:
	// Window
	sf::RenderWindow* window;
	int windowWidth = 1280;
	int windowHeight = 720;

	// GUI - Text
	sf::Font font;
	sf::Text titleText;
	sf::Text startText;
	sf::Text leaderboardText;
	sf::Text quitText;

	// User
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Final Output
	int finalOutput = 0;

	// Private Functions
	void initWindow();
	void initVariables();
	void initGUI();

public:
	// Constructor
	MainMenu();
	// Deconstructor
	virtual ~MainMenu();

	// Functions
	int run();
	void close();

	void updatePollEvents();
	void updateMousePosition();

	void updateGUI();
	void update();

	void renderGUI();
	void render();
};
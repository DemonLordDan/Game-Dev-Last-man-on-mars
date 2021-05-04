/*
Title: Leaderboard Header
Description: Creates all the required variables, functions, accessors and modifiers for the leaderboard class.
Author: Andrew Morrison
*/
#pragma once

#include<SFML/Graphics.hpp>
#include<map>
#include<string>
#include<sstream>
#include<iostream>

class Leaderboard
{
private:
	// Window
	sf::RenderWindow* window;
	int windowWidth = 1280;
	int windowHeight = 720;

	// GUI - Text
	sf::Font font;
	sf::Text titleText;
	sf::Text labels;
	sf::Text scores;
	sf::Text backText;

	// User
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Private Functions
	void initWindow();
	void initGUI();

public:
	// Constructor
	Leaderboard();
	// Deconstructor
	virtual ~Leaderboard();

	// Functions
	void run();
	void close();

	void updatePollEvents();
	void updateMousePosition();

	void updateGUI();
	void update();

	void renderGUI();
	void render();
};
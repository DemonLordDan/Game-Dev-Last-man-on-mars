/*
Title: Game Header
Description: Creates all the required variables, functions, accessors and modifiers for the game class.
Author: Andrew Morrison
*/
#pragma once

#include<map>
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

using namespace std;

class Game
{
private:
	// Window
	sf::RenderWindow* window;
	int windowWidth = 1280;
	int windowHeight = 720;

	// Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	// GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;
	sf::Text gameOverTextSecondary;

	sf::Text waveNumberText;

	// Shop GUI
	sf::Text shopText;
	sf::Text upgradeDmgText;
	sf::Text upgradeFirerateText;

	// World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	// Systems
	unsigned points;
	int waveNumber;
	bool shopOpen;
	bool gameOver;

	// Player
	Player* player;
	sf::Vector2f playerCenter;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;

	// PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	// Enemies
	float spawnTimer;
	float spawnTimerMax;
	float spawnTimerRate;
	std::vector<Enemy*> enemies;
	float maxEnemies; // Maximum enemies on screen at once
	float enemiesLeft;
	float enemiesPerRound;
	float enemySpeed; // Generic speed before changes

	// Variables
	string fileData;
	int LBwaveNumber[5];
	int LBpoints[5];

	// Private Functions
	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();

	void readFromFile();
	void writeToFile();

	void initPlayer();
	void initEnemies();

public:
	Game();
	virtual ~Game();

	// Functions
	void run();
	void death();

	void updatePollEvents();
	void updateMousePosition();
	void updateInput(float dt);
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets(float dt);
	void updateEnemies(float dt);
	void updateCombat(float dt);
	void updatePlayer(float dt);
	void updateWave();
	void updateShop();
	void update();

	void renderGUI();
	void renderWorld();
	void renderShop();
	void render();
};
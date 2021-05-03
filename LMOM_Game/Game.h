#pragma once

#include<map>
#include<string>
#include<sstream>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

using namespace sf;

class Game
{
private:
	// Window
	sf::RenderWindow* window;
	int windowWidth = 1920;
	int windowHeight = 1080;

	// Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	// GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;

	// World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	// Systems
	unsigned points;

	// Player
	Player* player;
	sf::Vector2f playerCenter;
	sf::Vector2f mousePosWindow;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;

	// PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	// Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	// misc
	int gameState;
	// Private Functions
	void sMenu();
	void prewarm();
	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();

	void initPlayer();
	void initEnemies();

public:
	Game();
	virtual ~Game();

	// Functions
	void run();

	void updatePollEvents();
	void updateInput(float dt);
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets(float dt);
	void updateEnemies(float dt);
	void updateCombat(float dt);
	void updatePlayer(float dt);
	void update();

	void renderGUI();
	void renderWorld();
	void render();
};
#pragma once


#include<SFML/Graphics.hpp>

class Enemy
{
private:
	sf::RectangleShape shape;
	int type;
	int hp;
	int hpMax;
	int damage;
	int points;
	float movementSpeed;

	sf::Vector2f currVelocity;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;

	// Private Functions
	void initVariables();
	void initShape();

public:
	Enemy(float pos_x, float pos_y, float movement_Speed);
	virtual ~Enemy();

	// Accessors
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	// Functions
	void update(float dt, sf::Vector2f player_Position);
	void render(sf::RenderTarget* target);
};
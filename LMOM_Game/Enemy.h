/*
Title: Enemy Header 
Description: Creates all the required variables, functions, accessors and modifiers for the enemy class.
Author: Andrew Morrison
*/

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
	void initVariables(float e_type, float e_hpMax, float e_damage, float e_points, float e_movement_Speed);
	void initShape(sf::Vector2f size, sf::Color color);

public:
	Enemy(float pos_x, float pos_y, float movement_Speed);
	virtual ~Enemy();

	// Accessors
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;
	const int& getHp() const;
	const int& getHpMax() const;

	// Modifiers
	void setHp(const int hp);
	void loseHp(const int value);

	// Functions
	void update(float dt, sf::Vector2f player_Position);
	void render(sf::RenderTarget* target);
};
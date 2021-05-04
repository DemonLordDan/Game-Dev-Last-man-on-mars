/*
Title: Bullet Header
Description: Creates all the required variables, functions, accessors and modifiers for the bullet class.
Author: Andrew Morrison
*/
#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include <iostream>

class Bullet
{
private:
	sf::Sprite shape;

	sf::Vector2f direction;
	sf::Vector2f currVelocity;
	float movementSpeed;

public:
	Bullet();
	Bullet(sf::Texture* texture, float pos_x, float pos_y, sf::Vector2f aimDirNorm, float movement_Speed);
	virtual ~Bullet();

	// Accessors
	const sf::FloatRect getBounds();

	// Functions
	void update(float dt);
	void render(sf::RenderTarget* target);
};
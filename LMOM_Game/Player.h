/*
Title: Player Header
Description: Creates all the required variables, functions, accessors and modifiers for the player class.
Author: Andrew Morrison
*/
#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include <iostream>

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;

	static sf::Clock clock;

	float attackCooldown;
	float attackCooldownMax;
	float cooldownMultiplier;

	int hp;
	int hpMax;
	int damage;

	// Private Functions
	void initVariables();
	void initTexture();
	void initSprite();

public:
	Player();
	Player(float pos_x, float pos_y);
	virtual ~Player();

	// Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;
	const int& getDamage() const;
	const int& getAttackCooldown() const;
	const int& getAttackCooldownMax() const;

	// Modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);
	void setDamage(const int dmg);
	void setCooldownMultiplier(const int cooldown);

	// Functions
	void move(const float dirX, const float dirY, const float dt);
	const bool canAttack();

	void updateAttack(float dt);
	void update(float dt);
	void render(sf::RenderTarget& target);
};
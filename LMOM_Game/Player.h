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

	int hp;
	int hpMax;

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

	// Modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);

	// Functions
	void move(const float dirX, const float dirY, const float dt);
	const bool canAttack();

	void updateAttack(float dt);
	void update(float dt);
	void render(sf::RenderTarget& target);
};
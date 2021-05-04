/*
Title: Enemy Class
Description: Handles the initialization of enemies along with functions dedicated to accessing and manipulating the enemies
Author: Andrew Morrison
*/
#include "Enemy.h"

/*
#########################
### Private Functions ###
#########################
*/
void Enemy::initShape(sf::Vector2f size, sf::Color color)
{
	this->shape.setSize(sf::Vector2f(size));
	this->shape.setFillColor(color);
}

void Enemy::initVariables(float e_type, float e_hpMax, float e_damage, float e_points, float e_movement_Speed)
{
	this->type		= e_type;
	this->hpMax		= e_hpMax;
	this->hp		= this->hpMax;
	this->damage	= e_damage;
	this->points	= e_points;
	this->movementSpeed = e_movement_Speed;
}

/*
###################
### Constructor ###
###################
*/
Enemy::Enemy(float pos_x, float pos_y, float movement_Speed)
{
	int randomEnemy;
	randomEnemy = rand() % 10;

	// Generic Enemy
	if (randomEnemy <= 5)
	{
		this->initVariables(0, 20, 1, 5, movement_Speed);
		this->initShape(sf::Vector2f(40.f, 40.f), sf::Color::Red);
		this->shape.setPosition(pos_x, pos_y);
	}
	// Big, Slow, High HP enemy
	else if (randomEnemy > 5 && randomEnemy < 9)
	{
		this->initVariables(1, 50, 1, 5, movement_Speed / 3);
		this->initShape(sf::Vector2f(100.f, 100.f), sf::Color::Yellow);
		this->shape.setPosition(pos_x, pos_y);
	}
	// Small, Fast, Low HP enemy
	else if (randomEnemy == 9)
	{
		this->initVariables(2, 10, 1, 20, movement_Speed * 3);
		this->initShape(sf::Vector2f(20.f, 20.f), sf::Color::Magenta);
		this->shape.setPosition(pos_x, pos_y);
	}
	// Default
	else
	{
		this->initVariables(0, 10, 1, 5, movement_Speed);
		this->initShape(sf::Vector2f(40.f, 40.f), sf::Color::Red);
		this->shape.setPosition(pos_x, pos_y);
	}

}

/*
#####################
### Deconstructor ###
#####################
*/
Enemy::~Enemy()
{

}

/*
#################
### Accessors ###
#################
*/
const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

const int& Enemy::getHp() const
{
	return this->hp;
}

const int& Enemy::getHpMax() const
{
	return this->hpMax;
}

/*
#################
### Modifiers ###
#################
*/
void Enemy::setHp(const int hp)
{
	this->hp = hp;
}

void Enemy::loseHp(const int value)
{
	this->hp -= value;

	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

/*
#################
### Functions ###
#################
*/
void Enemy::update(float dt, sf::Vector2f player_Position)
{
	// Calculates the normalised aim direction
	this->aimDir = player_Position - this->shape.getPosition();
	this->aimDirNorm = this->aimDir / static_cast<float>(sqrt(pow(this->aimDir.x, 2) + pow(this->aimDir.y, 2)));

	// Sets the enemies velocity
	this->currVelocity = aimDirNorm * this->movementSpeed;

	// Move the enemy
	this->shape.move(this->currVelocity * dt);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

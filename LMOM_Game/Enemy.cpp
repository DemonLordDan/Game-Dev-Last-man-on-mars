#include "Enemy.h"

/*
#########################
### Private Functions ###
#########################
*/
void Enemy::initShape()
{
	this->shape.setSize(sf::Vector2f(40.f, 40.f));
	this->shape.setFillColor(sf::Color::Red);
}

void Enemy::initVariables()
{
	this->type		= 0;
	this->hpMax		= 10;
	this->hp		= this->hpMax;
	this->damage	= 1;
	this->points	= 5;
	this->movementSpeed = 20.f;
}

/*
###################
### Constructor ###
###################
*/
Enemy::Enemy(float pos_x, float pos_y, float movement_Speed)
{
	this->initVariables();
	this->initShape();
	this->movementSpeed = movement_Speed;
	this->shape.setPosition(pos_x, pos_y);
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

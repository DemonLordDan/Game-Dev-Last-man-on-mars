#include "Bullet.h"

/*
###################
### Constructor ###
###################
*/
Bullet::Bullet()
{

}

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, sf::Vector2f aimDirNorm, float movement_Speed)
{
	this->shape.setTexture(*texture);

	this->shape.setPosition(pos_x, pos_y);
	this->currVelocity = aimDirNorm * movement_Speed;
	this->movementSpeed = movement_Speed;
}

/*
#####################
### Deconstructor ###
#####################
*/
Bullet::~Bullet()
{

}

/*
#################
### Accessors ###
#################
*/
const sf::FloatRect Bullet::getBounds()
{
	return this->shape.getGlobalBounds();
}

/*
#################
### Functions ###
#################
*/
void Bullet::update(float dt)
{
	// Direction
	//this->direction = Cam

	// Movement
	this->shape.move(this->currVelocity * dt);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

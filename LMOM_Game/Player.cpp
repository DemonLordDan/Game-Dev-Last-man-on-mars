#include "Player.h"

/*
#########################
### Private Functions ###
#########################
*/
void Player::initVariables()
{
	this->movementSpeed = 300.f;

	this->attackCooldownMax = 0.5f;
	this->attackCooldown = attackCooldownMax;

	this->hpMax = 10;
	this->hp = hpMax;
}

void Player::initTexture()
{
	// Load a texture from file
	if (!this->texture.loadFromFile("res/textures/player.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}
}

void Player::initSprite()
{
	// Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	// Resize the sprite
	this->sprite.scale(0.1f, 0.1f);
}

/*
###################
### Constructor ###
###################
*/
Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::Player(float pos_x, float pos_y)
{
	this->sprite.setPosition(pos_x, pos_y);
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

/*
#####################
### Deconstructor ###
#####################
*/
Player::~Player()
{

}

/*
#################
### Accessors ###
#################
*/
const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int & Player::getHp() const
{
	return this->hp;
}

const int & Player::getHpMax() const
{
	return this->hpMax;
}

/*
#################
### Modifiers ###
#################
*/
void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
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
void Player::move(const float dirX, const float dirY, const float dt)
{
	this->sprite.move(this->movementSpeed * dirX * dt, this->movementSpeed * dirY * dt);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}

	return false;
}

void Player::updateAttack(float dt)
{
	if (this->attackCooldown < this->attackCooldownMax)
	{
		this->attackCooldown += (1.f * dt);
	}
}

void Player::update(float dt)
{
	this->updateAttack(dt);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

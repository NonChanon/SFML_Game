#include "Enemy.h"
Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position, float hp) :
	animation(texture, imageCount, switchTime)
{
	this->hp = hp;
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(60.0f, 90.5f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
}
Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	velocity.x = -speed;
	velocity.y += 30.0f * deltaTime;

	if (velocity.x == 0.0f)
	{
		row = 0;
	}
	else {
		row = 0;
		if (velocity.x > 0.0f)
			faceRight = false;
		else
			faceRight = true;
	}
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Enemy::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//Collision on the left.
		speed = 3;
	}
	else if (direction.x > 0.0f)
	{
		//Collision on the right.
		speed = -3;
	}
	if (direction.y < 0.0f)
	{
		//Collision on the bottom.
		velocity.y = 0.0f;
	}
	else if (direction.y > 0.0f)
	{
		//Collision on the top.
		velocity.y = 0.0f;
	}
}


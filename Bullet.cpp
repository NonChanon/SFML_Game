#include "Bullet.h"
Bullet::Bullet(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speedx, float speedy, sf::Vector2f position, sf::Vector2f size, int type) :
	animation(texture, imageCount, switchTime)
{
	this->speedx = speedx;
	this->speedy = speedy;
	this->type = type;
	faceRight = true;
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
}
void Bullet::Update(float deltaTime)
{
	velocity.x = speedx;
	velocity.y = speedy;
	if (speedx > 0.0f) {
		faceRight = true;
	}
	else {
		faceRight = false;
	}
	animation.Update(0, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}
void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
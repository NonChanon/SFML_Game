#include "Item.h"
Item::Item(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position,unsigned int row):
	animation(texture, imageCount, switchTime)
{
	this->row = row;
	body.setSize(sf::Vector2f(40.0f, 60.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
}
Item::~Item()
{
}

void Item::Update(float deltaTime)
{
	velocity.x *= 0.0f;
	animation.Update(row, deltaTime,faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
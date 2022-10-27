#include "Splatform.h"
Splatform::Splatform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	row = 0;
	faceRight = true;
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
	hitbox.setOrigin(size / 2.0f);
	hitbox.setPosition(body.getPosition().x + 10, body.getPosition().y);
	hitbox.setSize(sf::Vector2f(60, 85));

}
Splatform::~Splatform()
{

}
void Splatform::Update(float deltaTime) {

}
void Splatform::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

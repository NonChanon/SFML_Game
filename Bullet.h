#pragma once
#include<SFML/Graphics.hpp>
#include "animation.h"
#include "Collider.h"
class Bullet
{
public:
	Bullet(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speedx, float speedy, sf::Vector2f position, sf::Vector2f size, int type);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void Oncollision(sf::Vector2f direction);
	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	void SetPosition(sf::Vector2f(position)) { body.setPosition(position); }
	float speedx;
	float speedy;
	bool faceRight;
	int getType() { return type; }
private:
	int type;
	sf::RectangleShape body;
	sf::RectangleShape texture;
	Animation animation;
	unsigned int row;
	sf::Vector2f velocity;
};
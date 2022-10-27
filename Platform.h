#pragma once
#include<SFML/Graphics.hpp>
#include"Collider.h"
#include "Animation.h"
class Platform
{
public:
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Platform();
	void Update(float deltatime);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f GetPosition() { return	body.getPosition(); }
	void OnCollision(sf::Vector2f direction);
	Collider GetCollider() { return Collider(body); }
private:
	sf::RectangleShape body;
	sf::Vector2f velocity;
};


#pragma once
#include<SFML/Graphics.hpp>
#include"Collider.h"
#include "Animation.h"
class Splatform
{
public:
	Splatform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Splatform();
	void Update(float deltatime);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f GetPosition() { return	body.getPosition(); }
	void OnCollision(sf::Vector2f direction);
	Collider GetCollider() { return Collider(hitbox); }
	bool faceRight;
private:
	unsigned int row;
	sf::RectangleShape body;
	sf::RectangleShape  hitbox;
};


#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
class Item
{
public:
	Item(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position, unsigned int row);
	~Item();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	sf::Vector2f GetPosition() { return	body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	void SetPosition(sf::Vector2f(position)) { body.setPosition(position); }
	bool faceRight;
	unsigned int ItemRow() { return row; }

private:
	sf::RectangleShape body;
	sf::RectangleShape  texture;
	Animation animation;
	unsigned int row;
	sf::Vector2f velocity;
};
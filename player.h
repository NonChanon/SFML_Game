#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "Item.h"
class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,float speed,float jumpHeight,float hp);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	void playerImmune();
	sf::Vector2f GetPosition() {return	body.getPosition();}
	Collider GetCollider() { return Collider(body); }
	float GetSpeed(){ return speed; }
	void SetPosition(sf::Vector2f(position)) { body.setPosition(position);}
	void rowItem(int itemRow);
	float hp;
	bool faceRight;
	int dmg;
	bool ch;
	bool immune;
	sf::Clock check;
	bool canJump;
	sf::Vector2f velocity;
	unsigned int row;
	int itemRow;
	float speed;
private:
	sf::Clock immuneClock;
	sf::RectangleShape body;
	sf::RectangleShape  texture;
	Animation animation;
	sf::Vector2f a;
	float jumpHeight;

};

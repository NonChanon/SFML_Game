#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
	class Enemy {
	public:
		Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,sf::Vector2f position,float hp);
		~Enemy();
		void Update(float deltaTime);
		void Draw(sf::RenderWindow& window);
		void OnCollision(sf::Vector2f direction);
		sf::Vector2f GetPosition() { return	body.getPosition(); }
		Collider GetCollider() { return Collider(body); }
		float GetSpeed() { return speed; }
		void SetPosition(sf::Vector2f(position)) { body.setPosition(position); }
		float hp;
		float speed;
		bool faceRight;
	private:
		sf::RectangleShape body;
		sf::RectangleShape  texture;
		Animation animation;
		unsigned int row;
		
		sf::Vector2f velocity;
		sf::Vector2f a;
	};




#include "Player.h"
#include "Item.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight, float hp) :
	animation(texture, imageCount, switchTime)
{
	this->hp = hp;
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	this->dmg = 35;
	row = 0;
	faceRight = true;
	ch = false;
	immune = false;

	body.setSize(sf::Vector2f(60.0f, 112.5f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(-255.0f, 200.0f);
	this->texture.setTexture(texture);
	this->texture.setSize(sf::Vector2f(100.0f, 112.5f));
	this->texture.setOrigin(body.getSize() / 2.0f);
	this->texture.setPosition(body.getPosition());
}
Player::~Player()
{
}

void Player::Update(float deltaTime)
{

	velocity.x *= 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canJump)
	{
		canJump = false;
		velocity.y = -sqrt(1.7f * 981.0f * jumpHeight);
	}
	velocity.y += 981.0f * deltaTime;

	if (velocity.x == 0.0f)
	{
		row = itemRow;
	}
	else
	{
		row = itemRow + 1;
		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}
	if (velocity.x == 0.0f && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		animation.switchTime = 0.2f;
		row = itemRow + 2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		animation.switchTime = 0.2f;
		row = itemRow + 3;
		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}
	else
	{
		animation.switchTime = 0.13f;
	}
	if (immune) {
		playerImmune();
	}
	else if (!immune) {
		immuneClock.restart();
	}
	animation.Update(row, deltaTime, faceRight);
	this->texture.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
	texture.setPosition(body.getPosition());
	if (!faceRight)
	{
		texture.setPosition(texture.getPosition().x - 60.0f, texture.getPosition().y);
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(this->texture);
}

void Player::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//Collision on the left.
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//Collision on the right.
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		//Collision on the bottom.
		velocity.y = 0.0f;
		canJump = true;
		//ch = false;
	}
	else if (direction.y > 0.0f)
	{
		//Collision on the top.
		velocity.y = 0.0f;
	}
}
void Player::rowItem(int itemRow)
{
	if (itemRow == 0)
	{
		dmg = 5;
		this->itemRow = 8;
	}
	else if (itemRow == 1)
	{
		dmg = 100;
		this->itemRow = 4;
	}
	else if (itemRow == 2)
	{
		dmg = 100;
		this->itemRow = 12;
	}
	else
	{
		dmg = 35;
		this->itemRow = 0;
	}

}
void Player::playerImmune()
{
	if (immuneClock.getElapsedTime().asMilliseconds() < 400)
	{
		texture.setFillColor(sf::Color(255, 255, 255, 150));
	}
	else if (immuneClock.getElapsedTime().asMilliseconds() < 800) {
		texture.setFillColor(sf::Color(255, 255, 255, 255));
	}
	else if (immuneClock.getElapsedTime().asMilliseconds() < 1200)
	{
		texture.setFillColor(sf::Color(255, 255, 255, 150));
	}
	else if (immuneClock.getElapsedTime().asMilliseconds() < 1600) {
		texture.setFillColor(sf::Color(255, 255, 255, 255));
	}
	else if (immuneClock.getElapsedTime().asMilliseconds() < 2000) {
		texture.setFillColor(sf::Color(255, 255, 255, 150));
	}
	else if (immuneClock.getElapsedTime().asMilliseconds() < 2400) {
		texture.setFillColor(sf::Color(255, 255, 255, 255));
		immune = false;
		immuneClock.restart();
	}
}


#define _CRT_SECURE_NO_WARNINGS
#define MENU 0
#define INGAME 1
#define LEADERBOARD 2
#define TUTORIAL 3
#define INPUTNAME 4
#define YOURSCORE 5
#define GAMEOVER 6
#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<stdio.h>
#include<utility>
#include<algorithm>
#include<string>
#include<iostream>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include"Player.h"
#include "Platform.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Splatform.h"
#include "Item.h"
#include "Textbox.h"

using namespace std;
void ResizeView(const sf::RenderWindow& window, sf::View& view);
void showHighScore(int x, int y, string word, sf::RenderWindow& window, sf::Font* font, int size);

static const float View_HEIGHT = 720.0f;

int main()
{
	//////////////////////////////////////////////////////// Clock //////////////////////////////////////////////////

	srand(time(NULL));
	sf::Clock clock;
	sf::Clock timeClock;
	sf::Clock playerClock;
	sf::Clock bullClock;
	sf::Clock row0Clock;
	sf::Clock row1Clock;
	sf::Clock row2Clock;
	sf::Clock fireClock;
	sf::Clock jumpClock;
	sf::Clock enemyClock;
	float timeJump = 0.0f;
	float fire = 0.0f;
	float row0clock = 0.0f;
	float row1clock = 0.0f;
	float row2clock = 0.0f;
	float deltaTime = 0.0f;
	float time = 0.0f;
	float pClock = 0.0f;
	float bull = 0;
	float eneClock = 0;

	//////////////////////////////////////////////////////// Set Default  //////////////////////////////////////////////////

	int items = 0;
	int i = 0;
	int state = 0;
	int rowItem = 3;
	string getName;
	int scoreIngame = 0;
	int x = 0;

	//////////////////////////////////////////////////////// Check Status //////////////////////////////////////////////////

	bool enemyCheck = false;
	bool Row0 = false;
	bool Row1 = false;
	bool Row2 = false;
	bool Row3 = false;
	bool Row4 = false;
	bool stopWalking = false;
	bool checkItem = false;
	bool exitToMenu = false;
	bool checkClick = false;

	//////////////////////////////////////////////////////// Setting //////////////////////////////////////////////////

	sf::RenderWindow window(sf::VideoMode(1000, 600), "Iron Bullet", sf::Style::Default);
	sf::RectangleShape frame(sf::Vector2f(1000.0f, 600.0f));
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(View_HEIGHT, View_HEIGHT));
	sf::Texture bullet_texture;
	sf::Texture player_texture;
	sf::Texture enemy_texture;
	sf::Texture item1;
	sf::Texture rocket_texture;
	sf::Texture Background;
	std::vector<Bullet> bullet;
	std::vector<Enemy> enemies;
	std::vector<Platform> platforms;
	std::vector<Splatform> splatforms;
	std::vector<Item> item;
	sf::Texture bag_texture;
	bag_texture.loadFromFile("bag.png");
	enemy_texture.loadFromFile("enemy.png");
	rocket_texture.loadFromFile("rocket.png");
	item1.loadFromFile("Item.png");
	player_texture.loadFromFile("Player2.png");
	bullet_texture.loadFromFile("Bullet.png");
	Background.loadFromFile("Background.jpg");
	if (!Background.loadFromFile("Background.jpg"))
	{
		printf("Failed");
	}
	sf::RectangleShape Bg(sf::Vector2f(11000, 720));
	Bg.setPosition(sf::Vector2f(-400, -360));
	Bg.setTexture(&Background);
	Player player(&player_texture, sf::Vector2u(6, 16), 0.1f, 175.0f, 200.0f, 100.0f);

	////////////////////////////////////////////////////////////// High Score //////////////////////////////////////////////////////////

	sf::Font font;
	font.loadFromFile("SgtJhonO-JRW07.ttf");
	Textbox textbox(30, sf::Color::Black, false, font, sf::Vector2f(400, 265));
	FILE* fp;
	char temp[255];
	int score[6];
	string name[6];
	vector <pair<int, string>> userScore;
	fp = fopen("score.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s", &temp);
		name[i] = temp;
		fscanf(fp, "%d", &score[i]);
		userScore.push_back(make_pair(score[i], name[i]));
		//cout << temp << " " << score;
	}
	name[5];
	score[5];
	userScore.push_back(make_pair(score[5], name[5]));
	sort(userScore.begin(), userScore.end());
	fclose(fp);
	fopen("score.txt", "w");
	for (int i = 5; i >= 1; i--)
	{
		strcpy(temp, userScore[i].second.c_str());
		fprintf(fp, "%s %d\n", temp, userScore[i].first);
	}
	fclose(fp);

	////////////////////////////////////////////// platforms ///////////////////////////////////////////////////

	platforms.push_back(Platform(nullptr, sf::Vector2f(100000.0f, 10.0f), sf::Vector2f(150.0f, 330.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(10.0f, 10.0f), sf::Vector2f(700.0f, 250.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(1210.0f, 10.0f), sf::Vector2f(100.0f, 210.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(2000.0f, 10.0f), sf::Vector2f(1700.0f, 305.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(1080.0f, 180.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(270.0f, 10.0f), sf::Vector2f(1310.0f, 50.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(1500.0f, 180.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(225.0f, 10.0f), sf::Vector2f(1670.0f, 50.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(250.0f, 10.0f), sf::Vector2f(1990.0f, 45.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(2190.0f, 180.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(9110.0f, 180.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(270.0f, 10.0f), sf::Vector2f(8880.0f, 50.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(8690.0f, 180.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(225.0f, 10.0f), sf::Vector2f(8520.0f, 50.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(250.0f, 10.0f), sf::Vector2f(8200.0f, 45.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(7990.0f, 180.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(2000.0f, 10.0f), sf::Vector2f(8500.0f, 305.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(1210.0f, 10.0f), sf::Vector2f(10100.0f, 210.0f)));

	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(2680.0f, 230.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(7500.0f, 230.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(130.0f, 10.0f), sf::Vector2f(3100.0f, 70.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(130.0f, 10.0f), sf::Vector2f(7100.0f, 70.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(130.0f, 10.0f), sf::Vector2f(3420.0f, 70.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(240.0f, 10.0f), sf::Vector2f(3710.0f, -80.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(130.0f, 10.0f), sf::Vector2f(5140.0f, 70.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(240.0f, 10.0f), sf::Vector2f(5430.0f, -80.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(50.0f, 10.0f), sf::Vector2f(3550.0f, -60.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(50.0f, 10.0f), sf::Vector2f(5270.0f, -60.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(50.0f, 10.0f), sf::Vector2f(3230.0f, -80.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(70.0f, 10.0f), sf::Vector2f(5850.0f, -80.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(70.0f, 10.0f), sf::Vector2f(4130.0f, -80.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(150.0f, 10.0f), sf::Vector2f(3960.0f, 40.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(50.0f, 10.0f), sf::Vector2f(3720.0f, 40.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(50.0f, 10.0f), sf::Vector2f(3695.0f, 170.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(50.0f, 10.0f), sf::Vector2f(5465.0f, 40.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(50.0f, 10.0f), sf::Vector2f(5420.0f, 170.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(150.0f, 10.0f), sf::Vector2f(5700.0f, 40.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(50.0f, 10.0f), sf::Vector2f(6960.0f, -80.0f)));
	splatforms.push_back(Splatform(&bag_texture, sf::Vector2f(90.0f, 100.0f), sf::Vector2f(2000.0f, 250.0f)));
	splatforms.push_back(Splatform(&bag_texture, sf::Vector2f(90.0f, 100.0f), sf::Vector2f(5000.0f, 300.0f)));
	splatforms.push_back(Splatform(&bag_texture, sf::Vector2f(90.0f, 100.0f), sf::Vector2f(3500.0f, 300.0f)));
	splatforms.push_back(Splatform(&bag_texture, sf::Vector2f(90.0f, 100.0f), sf::Vector2f(6000.0f, 300.0f)));
	splatforms.push_back(Splatform(&bag_texture, sf::Vector2f(90.0f, 100.0f), sf::Vector2f(8400.0f, 250.0f)));


	////////////////////////////////////////////// window ///////////////////////////////////////////////////
	bool checkBlock = true;
	bool lasershoot = false;

	sf::RectangleShape tutorial1(sf::Vector2f(1000, 600));
	tutorial1.setPosition(0, 0);

	sf::Texture tutorial_texture[2];
	tutorial_texture[0].loadFromFile("tutorial.png");
	tutorial_texture[1].loadFromFile("tutorial1.png");
	sf::RectangleShape leader1(sf::Vector2f(1000, 600));
	leader1.setPosition(0, 0);
	sf::Texture leader_texture[2];
	leader_texture[0].loadFromFile("leader.png");
	leader_texture[1].loadFromFile("leader1.png");
	sf::Texture menu_texture[5];
	sf::RectangleShape menu(sf::Vector2f(1000, 600));
	menu.setPosition(0, 0);
	sf::RectangleShape play(sf::Vector2f(145, 60));
	play.setPosition(800, 260);
	sf::RectangleShape leader(sf::Vector2f(450, 60));
	leader.setPosition(500, 340);
	sf::RectangleShape tutorial(sf::Vector2f(280, 60));
	tutorial.setPosition(670, 420);
	sf::RectangleShape quit(sf::Vector2f(145, 60));
	quit.setPosition(800, 500);
	sf::RectangleShape back(sf::Vector2f(100, 70));
	back.setPosition(50, 475);
	sf::RectangleShape water(sf::Vector2f(4700, 100));
	water.setPosition(2730, 270);
	sf::RectangleShape yourscore(sf::Vector2f(1000, 600));
	sf::Texture yourscore_texture[2];
	yourscore_texture[0].loadFromFile("score.png");
	yourscore_texture[1].loadFromFile("score1.png");
	sf::RectangleShape over(sf::Vector2f(1000, 600));
	sf::Texture over_texture[2];
	over_texture[0].loadFromFile("over.png");
	over_texture[1].loadFromFile("over1.png");
	water.setFillColor(sf::Color(0, 0, 0, 50));
	menu_texture[0].loadFromFile("menu.png");
	menu_texture[1].loadFromFile("menu1.png");
	menu_texture[2].loadFromFile("menu2.png");
	menu_texture[3].loadFromFile("menu3.png");
	menu_texture[4].loadFromFile("menu4.png");

	sf::Music background_music;
	background_music.openFromFile("background.wav");
	background_music.setLoop(true);
	background_music.setVolume(10);

	sf::Music missionClearM;
	missionClearM.openFromFile("missionclear.wav");
	//missionClearM.setLoop(true);
	missionClearM.setVolume(10);


	sf::Music gameOverM;
	gameOverM.openFromFile("gameover.wav");
	//gameOverM.setLoop(true);
	gameOverM.setVolume(10);


	sf::SoundBuffer playerM;
	playerM.loadFromFile("player.wav");
	sf::Sound player_music;
	player_music.setBuffer(playerM);
	//player_music.setLoop(true);
	player_music.setVolume(50);


	sf::SoundBuffer enemyM;
	enemyM.loadFromFile("enemy.wav");
	sf::Sound enemy_music;
	enemy_music.setBuffer(enemyM);
	//enemy_music.setLoop(true);
	enemy_music.setVolume(50);


	sf::SoundBuffer heavyM;
	heavyM.loadFromFile("heavy.wav");
	sf::Sound heavy_music;
	heavy_music.setBuffer(heavyM);
	//heavy_music.setLoop(true);
	heavy_music.setVolume(20);


	sf::SoundBuffer shortM;
	shortM.loadFromFile("shortgun.wav");
	sf::Sound short_music;
	short_music.setBuffer(shortM);
	//short_music.setLoop(true);
	short_music.setVolume(20);


	sf::SoundBuffer rocketM;
	rocketM.loadFromFile("rocket.wav");
	sf::Sound rocket_music;
	rocket_music.setBuffer(rocketM);
	//rocket_music.setLoop(true);
	rocket_music.setVolume(50);


	sf::SoundBuffer itemM;
	itemM.loadFromFile("item.wav");
	sf::Sound item_music;
	item_music.setBuffer(itemM);
	//item_music.setLoop(true);
	item_music.setVolume(70);

	sf::SoundBuffer gunM;
	gunM.loadFromFile("gun.wav");
	sf::Sound gun_music;
	gun_music.setBuffer(gunM);
	//gun_music.setLoop(true);
	gun_music.setVolume(50);


	sf::SoundBuffer clickM;
	clickM.loadFromFile("click.wav");
	sf::Sound click_music;
	click_music.setBuffer(clickM);
	//click_music.setLoop(true);
	click_music.setVolume(100);

	sf::RectangleShape nameInput(sf::Vector2f(1000, 600));
	sf::Texture name_texture;
	name_texture.loadFromFile("inputname.png");
	while (1) {
		while (window.isOpen())
		{

			window.clear();
			window.setView(window.getDefaultView());
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					ResizeView(window, view);
					break;
				case sf::Event::TextEntered:
					textbox.typedOn(event);
					break;
				}
			}
			std::cout << textbox.getName() << std::endl;
			if (state == MENU)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
				}
				menu.setTexture(&menu_texture[0]);
				background_music.stop();
				gameOverM.stop();
				missionClearM.stop();


				if (play.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					menu.setTexture(&menu_texture[1]);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						click_music.play();
						state = 4;
					}
				}
				if (leader.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						click_music.play();
						state = 2;
					}
					menu.setTexture(&menu_texture[2]);
				}
				if (tutorial.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						click_music.play();
						state = 3;
					}
					menu.setTexture(&menu_texture[3]);
				}
				if (quit.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						click_music.play();
						window.close();
					}
					menu.setTexture(&menu_texture[4]);
				}
				enemyClock.restart();
				clock.restart();
				timeClock.restart();
				playerClock.restart();
				bullClock.restart();
				row0Clock.restart();
				row1Clock.restart();
				row2Clock.restart();
				fireClock.restart();
				jumpClock.restart();
				enemies.erase(enemies.begin(), enemies.end());
				item.erase(item.begin(), item.end());
				player.SetPosition(sf::Vector2f(-255.0f, 200.0f));
				enemyCheck = false;
				Row0 = false;
				Row1 = false;
				Row2 = false;
				Row3 = false;
				Row4 = false;
				stopWalking = false;
				checkItem = false;
				exitToMenu = false;
				items = 0;
				i = 0;
				rowItem = 3;
				scoreIngame = 0;
				x = 0;
				view.setCenter(sf::Vector2f(x, 0));
				player.hp = 100;
				player.faceRight = true;
				player.immune = false;
				window.draw(menu);
				textbox.resetString();
			}
			if (state == LEADERBOARD)
			{
				leader1.setTexture(&leader_texture[0]);
				if (back.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					leader1.setTexture(&leader_texture[1]);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						state = 0;
					}
				}
				window.draw(leader1);
				showHighScore(430, 150, userScore[5].second, window, &font, 35);
				showHighScore(530, 150, to_string(userScore[5].first), window, &font, 35);
				showHighScore(430, 215, userScore[4].second, window, &font, 35);
				showHighScore(530, 215, to_string(userScore[4].first), window, &font, 35);
				showHighScore(430, 280, userScore[3].second, window, &font, 35);
				showHighScore(530, 280, to_string(userScore[3].first), window, &font, 35);
				showHighScore(430, 345, userScore[2].second, window, &font, 35);
				showHighScore(530, 345, to_string(userScore[2].first), window, &font, 35);
				showHighScore(430, 410, userScore[1].second, window, &font, 35);
				showHighScore(530, 410, to_string(userScore[1].first), window, &font, 35);
			}
			if (state == TUTORIAL)
			{
				tutorial1.setTexture(&tutorial_texture[0]);
				if (back.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					tutorial1.setTexture(&tutorial_texture[1]);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						state = 0;
					}
				}
				window.draw(tutorial1);
			}
			if (state == INPUTNAME)
			{

				nameInput.setTexture(&name_texture);
				window.draw(nameInput);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && textbox.getName() != "")
				{
					click_music.play();
					state = 1;
				}
				getName = textbox.getName();
				textbox.Update(sf::Mouse::getPosition(window));
				textbox.Draw(window);
			}
			if (state == YOURSCORE) {
				yourscore.setTexture(&yourscore_texture[0]);
				if (back.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					yourscore.setTexture(&yourscore_texture[1]);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						state = 0;
						char temp[255];
						int score[6];
						string name[6];
						vector <pair<int, string>> userScore;
						fp = fopen("score.txt", "r");
						for (int i = 0; i < 5; i++)
						{
							fscanf(fp, "%s", &temp);
							name[i] = temp;
							fscanf(fp, "%d", &score[i]);
							userScore.push_back(make_pair(score[i], name[i]));
							//cout << temp << " " << score;
						}
						name[5] = getName;
						score[5] = scoreIngame;
						userScore.push_back(make_pair(score[5], name[5]));
						sort(userScore.begin(), userScore.end());
						fclose(fp);
						fopen("score.txt", "w");
						for (int i = 5; i >= 1; i--)
						{
							strcpy(temp, userScore[i].second.c_str());
							fprintf(fp, "%s %d\n", temp, userScore[i].first);
						}

						fclose(fp);
					}

				}
				window.draw(yourscore);
				if(scoreIngame < 100) showHighScore(500, 280, to_string(scoreIngame), window, &font, 50);
				else if(scoreIngame < 1000) showHighScore(440, 280, to_string(scoreIngame), window, &font, 50);
				else if (scoreIngame < 10000) showHighScore(410, 280, to_string(scoreIngame), window, &font, 50);
				else if (scoreIngame < 100000) showHighScore(380, 280, to_string(scoreIngame), window, &font, 50);
				else if (scoreIngame < 1000000) showHighScore(350, 280, to_string(scoreIngame), window, &font, 50);
			}
			if (state == INGAME) 
			{
				background_music.play();
				exitToMenu = false;
				break;
			}
			if (state == GAMEOVER)
			{
				over.setTexture(&over_texture[0]);
				if (back.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					over.setTexture(&over_texture[1]);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						state = 0;
					}
				}
				window.draw(over);
			}
			std::cout << textbox.getName() << std::endl;
			window.display();
		}

		while (window.isOpen() && exitToMenu == false)
		{
			window.clear();
			window.draw(Bg);
			sf::Event event;
			deltaTime = clock.restart().asSeconds();
			if (deltaTime > 1.0f / 20.0f)
				deltaTime = 1.0f / 20.0f;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					ResizeView(window, view);
					break;
				case sf::Event::TextEntered:
					textbox.typedOn(event);
					break;
				}
			}
			if (state == INGAME) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
				}
				////////////////////////////////////////////// player view ///////////////////////////////////////////////////
				player.Update(deltaTime);
				if (player.GetPosition().x >= i)
				{
					view.setCenter(sf::Vector2f(player.GetPosition().x, 0));
					i++;
				}
				if (player.GetPosition().x < x - 310 && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					player.speed = 0;
				}
				else
				{
					player.speed = 175;
				}
				if (player.GetPosition().x >= x)
				{
					x++;
				}
				////////////////////////////////////////////// Check Collision & Random Case ///////////////////////////////////////////////////

				timeJump = jumpClock.getElapsedTime().asMilliseconds();
				sf::Vector2f direction;
				for (Platform& platform : platforms)
				{
					Collider playerCollision = player.GetCollider();

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (player.velocity.y != 0 && player.velocity.y < 100))
					{
						checkBlock = false;
						jumpClock.restart();
					}
					if (checkBlock == false && timeJump >= 250)
					{
						checkBlock = true;
					}

					if (checkBlock == true && player.GetPosition().y + 56.25f > platform.GetPosition().y - 5)
					{
						if (platform.GetCollider().CheckCollision(playerCollision, direction, 1.0f))
							player.OnCollision(direction);
					}

					for (Enemy& enemy : enemies)
					{
						enemy.Update(deltaTime);
						Collider enemyCollision = enemy.GetCollider();
						if (platform.GetCollider().CheckCollision(enemyCollision, direction, 1.0f))
							enemy.OnCollision(direction);
						pClock = playerClock.getElapsedTime().asMilliseconds();
						if (!player.immune)
						{
							if (enemy.GetCollider().CheckCollision(playerCollision, direction, 1.0f))
							{
								player_music.play();
								player.immune = true;
								if (pClock > 1000)
								{
									player.hp -= 35.0f;
									playerClock.restart();
								}
							}

						}
						if (player.hp <= 0)
						{
							enemies.erase(enemies.begin(), enemies.end());
							background_music.stop();
							exitToMenu = true;
							window.setView(window.getDefaultView());
							state = 6;
							gameOverM.play();
						}
					}
				}
				for (Splatform& splatform : splatforms)
				{
					Collider playerCollision = player.GetCollider();
					if (splatform.GetCollider().CheckCollision(playerCollision, direction, 1.0f))
					{
						player.OnCollision(direction);
					}
					for (Enemy& enemy : enemies)
					{
						enemy.Update(deltaTime);
						Collider enemyCollision = enemy.GetCollider();
						if (splatform.GetCollider().CheckCollision(enemyCollision, direction, 1.0f))
							enemy.OnCollision(direction);
					}
					for (int i = 0; i < bullet.size(); i++)
					{
						Collider bulletCollision = bullet[i].GetCollider();
						if (splatform.GetCollider().CheckCollision(bulletCollision, direction, 1.0f))
						{
							bullet.erase(bullet.begin() + i);
						}
					}
				}
				eneClock = enemyClock.getElapsedTime().asMilliseconds();
				for (int j = 0; j < enemies.size(); j++)
				{
					Collider enemyCollision = enemies[j].GetCollider();
					for (int i = 0; i < bullet.size(); i++)
					{
						if (bullet[i].GetCollider().CheckCollision(enemyCollision, direction, 1.0f))
						{
							enemyClock.restart();
							enemies[j].hp -= player.dmg;
							if (bullet[i].getType() != 2)
							{
								bullet.erase(bullet.begin() + i);
							}
							if (enemies[j].hp <= 0)
							{
								enemy_music.play();
								scoreIngame += 100;
								items = rand() % 30;
								switch (items)
								{
								case(0): case(1): case(2):
									item.push_back(Item(&item1, sf::Vector2u(2, 3), 0.2f, sf::Vector2f(enemies[j].GetPosition().x, enemies[j].GetPosition().y), 0));
									break;

								case(3): case(4): case(5):
									item.push_back(Item(&item1, sf::Vector2u(2, 3), 0.2f, sf::Vector2f(enemies[j].GetPosition().x, enemies[j].GetPosition().y), 1));
									break;

								case(6): case(7): case(8):
									item.push_back(Item(&item1, sf::Vector2u(2, 3), 0.2f, sf::Vector2f(enemies[j].GetPosition().x, enemies[j].GetPosition().y), 2));
									break;
								}
								enemies.erase(enemies.begin() + j);
							}
						}
					}
				}
				for (int i = 0; i < item.size(); i++)
				{
					Collider playerCollider = player.GetCollider();
					if (item[i].GetCollider().CheckCollision(playerCollider, direction, 1.0f))
					{
						item_music.play();
						checkItem = true;
						rowItem = item[i].ItemRow();
						switch (item[i].ItemRow())
						{
						case(0):
							row0Clock.restart();
							Row0 = true;
							Row1 = false;
							Row2 = false;
							break;
						case(1):
							row1Clock.restart();
							Row0 = false;
							Row1 = true;
							Row2 = false;
							break;
						case(2):
							row2Clock.restart();
							Row0 = false;
							Row1 = false;
							Row2 = true;
							break;
						}
						item.erase(item.begin() + i);
					}
				}

				if (checkItem)player.rowItem(rowItem);
				else player.rowItem(3);

				for (int b = 0; b < bullet.size(); b++)
				{
					if (bullet[b].GetPosition().x >= player.GetPosition().x + 600)
					{
						bullet.erase(bullet.begin() + b);
					}
				}
				for (Platform& platform : platforms)
				{
					for (int i = 0; i < bullet.size(); i++)
					{
						Collider bulletCollision = bullet[i].GetCollider();
						if (platform.GetCollider().CheckCollision(bulletCollision, direction, 1.0f))
						{
							bullet.erase(bullet.begin() + i);
						}
					}
				}

				//////////////////////////////////////////////////Enemy//////////////////////////////////////////////////////
				time = timeClock.getElapsedTime().asMilliseconds();
				if (player.GetPosition().x > 500 && player.GetPosition().x < 2000 && time > 4000)
				{
					enemies.push_back(Enemy(&enemy_texture, sf::Vector2u(12, 1), 3.0f, 3.0f, sf::Vector2f(player.GetPosition().x + 400 + rand() % 501, -500.0f), 100.0f));
					timeClock.restart();

				}
				else if (player.GetPosition().x > 2000 && player.GetPosition().x < 6000 && time > 4000)
				{
					enemies.push_back(Enemy(&enemy_texture, sf::Vector2u(12, 1), 3.0f, 3.0f, sf::Vector2f(player.GetPosition().x + 400 + rand() % 501, -500.0f), rand() % 51 +100.0f));
					timeClock.restart();
				}
				else if (player.GetPosition().x > 6000 && player.GetPosition().x < 9600 && time > 3000)
				{
					enemies.push_back(Enemy(&enemy_texture, sf::Vector2u(12, 1), 3.0f, 4.0f, sf::Vector2f(player.GetPosition().x + 400 + rand() % 501, -500.0f), rand() % 51 + 100.0f));
					timeClock.restart();
				}
				if (player.GetPosition().x >= 10200)
				{
					missionClearM.play();
					background_music.stop();
					exitToMenu = true;
					window.setView(window.getDefaultView());
					state = 5;
				}
				bull = bullClock.getElapsedTime().asMilliseconds();
				if (bull > 400 && !Row0 && !Row1 && !Row2)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.faceRight == true)
					{
						gun_music.play();
						bullet.push_back(Bullet(&bullet_texture, sf::Vector2u(1, 1), 0.0f, 500.0f, 0, sf::Vector2f(player.GetPosition().x + 20, player.GetPosition().y - 10), sf::Vector2f(10, 10), 3));
						bullClock.restart();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.faceRight == false)
					{
						gun_music.play();
						bullet.push_back(Bullet(&bullet_texture, sf::Vector2u(1, 1), 0.0f, -500.0f, 0, sf::Vector2f(player.GetPosition().x - 20, player.GetPosition().y - 10), sf::Vector2f(10, 10), 3));
						bullClock.restart();
					}
				}
				if (bull > 100 && Row0 && !Row1 && !Row2)
				{

					if (row0Clock.getElapsedTime().asMilliseconds() < 5000 && Row0 && !Row1 && !Row2)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.faceRight == true)
						{
							heavy_music.play();
							bullet.push_back(Bullet(&bullet_texture, sf::Vector2u(1, 1), 0.0f, 500.0f, 0, sf::Vector2f(player.GetPosition().x + 35, player.GetPosition().y + 10), sf::Vector2f(25, 10), 0));
							bullet.push_back(Bullet(&bullet_texture, sf::Vector2u(1, 1), 0.0f, 500.0f, 0, sf::Vector2f(player.GetPosition().x + 50, player.GetPosition().y), sf::Vector2f(25, 10), 0));
							bullet.push_back(Bullet(&bullet_texture, sf::Vector2u(1, 1), 0.0f, 500.0f, 0, sf::Vector2f(player.GetPosition().x + 40, player.GetPosition().y - 10), sf::Vector2f(25, 10), 0));
							bullClock.restart();
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.faceRight == false)
						{
							heavy_music.play();
							bullet.push_back(Bullet(&bullet_texture, sf::Vector2u(1, 1), 0.0f, -500.0f, 0, sf::Vector2f(player.GetPosition().x - 35, player.GetPosition().y + 10), sf::Vector2f(25, 10), 0));
							bullet.push_back(Bullet(&bullet_texture, sf::Vector2u(1, 1), 0.0f, -500.0f, 0, sf::Vector2f(player.GetPosition().x - 40, player.GetPosition().y), sf::Vector2f(25, 10), 0));
							bullet.push_back(Bullet(&bullet_texture, sf::Vector2u(1, 1), 0.0f, -500.0f, 0, sf::Vector2f(player.GetPosition().x - 50, player.GetPosition().y - 10), sf::Vector2f(25, 10), 0));
							bullClock.restart();
						}
					}
					else
					{
						checkItem = false;
						row0Clock.restart();
						Row0 = false;
					}

				}
				if (bull > 600 && !Row0 && Row1 && !Row2)
				{
					if (row1Clock.getElapsedTime().asMilliseconds() < 5000 && !Row0 && Row1 && !Row2)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.faceRight == true)
						{
							short_music.play();
							bullet.push_back(Bullet(&bullet_texture, sf::Vector2u(1, 1), 0.0f, 400.0f, 0.0f, sf::Vector2f(player.GetPosition().x + 30, player.GetPosition().y), sf::Vector2f(20, 15), 1));
							bullClock.restart();
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.faceRight == false)
						{
							short_music.play();
							bullet.push_back(Bullet(&bullet_texture, sf::Vector2u(1, 1), 0.0f, -400.0f, 0.0f, sf::Vector2f(player.GetPosition().x - 30, player.GetPosition().y), sf::Vector2f(20, 15), 1));
							bullClock.restart();
						}
					}
					else
					{
						checkItem = false;
						row1Clock.restart();
						Row1 = false;
					}
				}
				if (bull > 400 && !Row0 && !Row1 && Row2)
				{
					if (row2Clock.getElapsedTime().asMilliseconds() < 5000 && !Row0 && !Row1 && Row2)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.faceRight == true)
						{
							rocket_music.play();
							bullet.push_back(Bullet(&rocket_texture, sf::Vector2u(2, 1), 0.1f, 300.0f, 0.0f, sf::Vector2f(player.GetPosition().x + 30, player.GetPosition().y), sf::Vector2f(50, 30), 1));
							bullClock.restart();
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.faceRight == false)
						{
							rocket_music.play();
							bullet.push_back(Bullet(&rocket_texture, sf::Vector2u(2, 1), 0.1f, -300.0f, 0.0f, sf::Vector2f(player.GetPosition().x - 30, player.GetPosition().y), sf::Vector2f(50, 30), 1));
							bullClock.restart();
						}
					}
					else
					{
						checkItem = false;
						row2Clock.restart();
						Row2 = false;
					}
				}

				window.setView(view);
				player.Draw(window);

				for (Enemy& enemy : enemies)
					enemy.Draw(window);
				for (Bullet& bullet : bullet)
				{
					bullet.Draw(window);
					bullet.Update(deltaTime);
				}
				for (Splatform& splatforms : splatforms)
				{
					splatforms.Draw(window);
					splatforms.Update(deltaTime);
				}
				for (Platform& platforms : platforms)
				{
					platforms.Update(deltaTime);
				}
				for (Item& item : item)
				{
					item.Draw(window);
					item.Update(deltaTime);
				}
				window.draw(water);
				showHighScore(x + 150, -300, "SCORE", window, &font, 32);
				showHighScore(x + 280, -300, to_string(scoreIngame), window, &font, 32);
			}

			window.display();
		}
	}
	return 0;
}


//////////////////////////////////////////////////////// Function //////////////////////////////////////////////////

void showHighScore(int x, int y, string word, sf::RenderWindow& window, sf::Font* font, int size)
{
	sf::Text text;
	text.setFont(*font);
	text.setPosition(x, y);
	text.setString(word);
	text.setCharacterSize(size);
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color(168, 144, 68));
	text.setOutlineThickness(2);
	window.draw(text);
}
void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize((View_HEIGHT)*aspectRatio, View_HEIGHT);
}

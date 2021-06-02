#pragma once
#include <SFML/Graphics.hpp>
#include "GameObjects.h"
#include "Factory.h"
#include "Battle.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace sf;
using namespace std;

class Level {
public: 
	Level();
	Sprite backgroundSprite;
	Texture backgroundTexture;
	Texture tileSet;
	RectangleShape tile;
	FloatRect endPoint;
	Vector2i mapSize, tileIDcord;
	Vector2f resolution, spawnPoint, viewCord;
	Battle battle;

	std::vector <Item*> items;
	std::vector <Friend> friends;
	std::vector <Enemy> enemies;
	int tileSetWidth,blockSize;
	int** map;
	std::string fileName;
	void calculateTile(int tileID);
	void readSpawnPoint(ifstream &in);
	void readFriend(ifstream &in);
	void readEnemy(ifstream &in);
	void readItem(ifstream &in);
	void readEndPoint(ifstream &in);
	void drawMap(RenderWindow& window);
	void drawBackground(RenderWindow& window);
	void drawEnemies(RenderWindow& window);
	void drawFriends(RenderWindow& window);
	void drawItems(RenderWindow& window);
public:
	void loadLVL(const std::string fileName, Player &_player, RenderWindow &window);
	void draw(RenderWindow& window);
	void worldUpdate(Player& player, Clock &clock, Vector2f viewCenter);
	void clear();
};
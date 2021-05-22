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

class Level {
public: 
	Level();
	Sprite backgroundSprite;
	Texture backgroundTexture;
	Texture tileSet;
	RectangleShape tile;
	Vector2i mapSize,tileIDcord;
	Vector2f resolution, spawnPoint;
	Battle battle;
	Player player;
	std::vector <Item> items;
	std::vector <Friend> friends;
	std::vector <Enemy> enemies;
	int tileSetWidth,blockSize;
	int** map;
	std::string fileName;
	void calculateTile(int tileID);
	void drawMap(RenderWindow& window, View view);
	void drawBackground(RenderWindow& window, View view);
	void drawEnemies(RenderWindow& window, View view);
	void drawFriends(RenderWindow& window, View view);
	void drawItems(RenderWindow& window, View view);
public:
	void loadLVL(const std::string fileName, Player &_player, RenderWindow &window);
	void draw(RenderWindow& window, View view);
	void worldUpdate();
	void clear();
};
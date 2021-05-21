#pragma once
#include <SFML/Graphics.hpp>
#include "GameObjects.h"
#include "Factory.h"
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
	std::vector <Item> items;
	std::vector <Friend> friends;
	std::vector <Enemy> enemies;
	int tileSetWidth,blockSize;
	int** map;
	std::string fileName;
public:
	void loadLVL(const std::string fileName);
	void drawMap(RenderWindow &window, View view);
	void drawBackground(RenderWindow &window, View view);
	void draw(RenderWindow& window, View view);
	void calculateTile(int tileID);
	void worldUpdate();
};
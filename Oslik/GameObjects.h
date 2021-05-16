#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

using namespace sf;

class GameObject {
public:
	FloatRect hitBox;
	Texture texture;
	Sprite sprite;
	String name;
public:
	Sprite getSprite();
	void setHitBox(FloatRect _hitBox);
	FloatRect getHitBox();
};

class Item : public GameObject {
public:
	Texture textureInInventory;
	Sprite spriteInInventory;
};


class Equipment : public Item {
public:
	void putOn();
};

class Consumable : public Item {
public:
	String name;
	int maxQuantity;
public:
	Consumable();
	void consume();
	Sprite getSpriteInInventory();
};

class Cell {
public:
	FloatRect hitBox;
	Item *item;
	bool isEmpty = true;
	int count = 0;
};

class Inventory : public GameObject {
public:
	Cell consumable[8];
	RectangleShape attackBar, hpBar;
	int quantityConsum, quantityEquip;

public:
	Inventory();
	void open(RenderWindow &window);
	void addItem(Consumable& item);
	void addItem(Equipment item);
};

class Character : public GameObject {
public:
	AnimationManager animation;
	struct characteristics {
		int HP,
			MP,
			ATK,
			DEF,
			Level,
			Exp;
	} stats;
public:
	void setAnimationTexture();
	void attack();
	characteristics getStats();
};

class Player : public Character {
public:
	int dx = 0, dy = 0, speed = 400, g = 2000, blockSize;
	int** map;
	bool onGround, running;
	Inventory inventory;
public:
	Player() {}
	void initialize(String fileName, int**& map, int blockSize, Vector2f spawnPoint);
	void update(float time);
	void moveLeft(float time);
	void moveRight(float time);
	void jump();
	void run();
	void stopRun();
	void stopX();
	void gravity(float time);
	void collisionX();
	void collisionY();
	void openInventory(RenderWindow& window);
};

class Friend : public GameObject {

};

class Enemy : public Character {
	
};

class Swordsman : public Enemy {

public:
	Swordsman(int _x, int _y);
};

class Fister : public Enemy {

public:
	Fister(int _x, int _y);
};

class Berserk : public Enemy {

public:
	Berserk(int _x, int _y);
};
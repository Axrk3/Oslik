#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

using namespace sf;

class GameObject {
public:
	Vector2f position;
	FloatRect rect;
	Texture texture;
	Sprite sprite;
	String name;
public:
	Sprite getSprite();
	void setRect(FloatRect _rect);
	FloatRect getRect();
};

class Item : public GameObject {
	Texture textureInInventory;
	Sprite spriteInInventory;
};


class Equipment : public Item {
public:

public:
	void putOn();
};

class Consumable : public Item {
public:

public:
	Consumable();
	void consume();
};

class Inventory {
public:
	Consumable consum[12];
	Equipment equip[12];
	int quantityConsum, quantityEquip;
	RectangleShape rect;
	Vector2f scale;
public:
	Inventory();
	void open();
	void addItem(Consumable item, String itemName);
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
			Exp,
			initiative;
	} stats;
public:
	void setAnimationTexture();
	void fight();
	void getStats();
};

class Friend : public Character {

};

class Enemy : public Character {

};

class Player : public Character {
public:	
	int dx = 0, dy = 0, speed = 400, g = 1000, blockSize;
	int** map;
	bool onGround, running;
public:
	Player() {}
	void initialize(String fileName,int** &map, int blockSize);
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
};

/*
class GameObject {
public:
	Vector2f position;
	FloatRect rect;
	Texture texture;
	Sprite sprite;
public:
	String name;
	Sprite getSprite();
	void setRect(int id, int value);
	FloatRect getRect();
};

class Item : public GameObject {
	int quantity;
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

};

class Inventory {
public:
	Consumable consum[12];
	Equipment equip[12];
	int quantityConsum, quantityEquip;
	RectangleShape rect;
	Vector2f scale;
	// Сделать смещение player.sprite.setPosition(player.rect.left - offsetX, player.rect.top - offsetY);
public:
	Inventory();
	void open();
	void addItem(Consumable item, String itemName);
	void addItem(Equipment item);
};

class Character : public GameObject {
public:
	struct characteristics {
		int HP,
			MP,
			ATK,
			DEF,
			Level,
			Exp,
			initiative;
	} stats;
public:
	void fight();
	void getStats();
};

class Friend : public Character {

};

class Enemy : public Character {
	void drop();
};

class Player : public Character {
public:
	int ground;
	bool jump;
	Inventory inventory;
public:
	Player();
	float dx, dy;
	void Jump();
};
*/

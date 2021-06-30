#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"

using namespace sf;

class Player;

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
protected:
	String name, discription;
	int coefficient, id;
	Texture textureInInventory;
	Sprite spriteInInventory;
public:
	Item(String _name, int _coefficient);

	virtual bool playerIntersection(Player &player);
	virtual void use(Player &player) {};
	virtual String examine();
	virtual int getID();
	virtual int getCoefficient();

	Sprite getSpriteInInventory();
};

class Equipment : public Item {
public:
	Equipment(String _name, int _coefficient) : Item(_name, _coefficient) {};
};

class Helmet : public Equipment {
public:
	Helmet(String _name, int _id, int _coefficient) : Equipment(_name, _coefficient) { 
		discription = "Gives 3 points of armor while equiped."; 
		id = _id;
	};
	void use(Player& player);
};

class Saddle : public Equipment {
public:
	Saddle(String _name, int _id, int _coefficient) : Equipment(_name, _coefficient) { 
		discription = "Gives 5 points of armor while equiped."; 
		id = _id;
	};
	void use(Player& player);
};

class Horseshoe : public Equipment {
public:
	Horseshoe(String _name, int _id, int _coefficient) : Equipment(_name, _coefficient) { 
		discription = "Gives 2 points of armor while equiped.";
		id = _id;
	};
	void use(Player& player);
};

class Consumable : public Item {
public:
	Consumable(String _name, int _coefficient) : Item(_name, _coefficient) {};
};

class HealthPotion : public Consumable {
private:

public: 
	HealthPotion(String _name, int _id, int _coefficient) : Consumable(_name, _coefficient) { 
		discription = "Heals 10 HP."; 
		id = _id;
	};
	void use(Player &player);
};

class StrengthPotion : public Consumable {
public:
	StrengthPotion(String _name, int _id, int _coefficient) : Consumable(_name, _coefficient) { 
		discription = "Increases strenght by one.";
		id = _id;
	};
	void use(Player &player);
};

class ResistancePotion : public Consumable {
public:
	ResistancePotion(String _name, int _id, int _coefficient) : Consumable(_name, _coefficient) { 
		discription = "Increases armor by one.";
		id = _id;
	};
	void use(Player &player);
};

class Cell {
public:
	FloatRect hitBox;
	Item *item;
	bool isEmpty;

	void drop();
};

class Character : public GameObject {
public:
	AnimationManager animation;
	struct characteristics {
		int HP,
			ATK,
			DEF;
	} stats;
public:
	void setAnimationTexture();
	void attack();
	characteristics getStats();
	void setStats(characteristics _stats);
};

class Inventory : public GameObject {
public:
	Cell cells[8];
	Cell equipmentCells[3];

	RectangleShape inventoryBars[3];
	FloatRect buttons[3];
	Vector2f mousePosition;
	int quantityConsum, quantityEquip, openedCell, openedEquipmentCell, activeButton;
	

	Texture menuTexture;
	Sprite menuSprite, buttonSprite;
	Font font;
	Text text;
	
	bool isClicked = false, isExamine = false;
public:
	Inventory();
	void draw(RenderWindow &window);
	void input(Player &player);
	void addItem(Item &item);
	void addItem(Item &item, int index);
	void equipItem();
	void menuLogic(Player &player);
	void update(Character::characteristics stats, Vector2f viewCenter);
	void updateCells();
	void updateEquipmentCells();
	void updateBars(Character::characteristics stats);
	void updateItemsIcons();
	void updateButtons();
	void clear();
};

class Player : public Character {
public:
	int dx = 0, dy = 0, speed = 400, g = 2000, blockSize;
	int** map;
	bool onGround, running;
	Inventory inventory;
public:
	Player();
	void initialize(String fileName, int **&map);
	void update(float time,Vector2f viewCenter);
	void moveLeft(float time);
	void moveRight(float time);
	void jump();
	void run();
	void stopRun();
	void stopX();
	void gravity(float time);
	void collisionX();
	void collisionY();
	void setSpawnPoint(Vector2f spawnPoint);
	void openInventory(RenderWindow& window, Vector2f viewCenter);
};

class Friend : public GameObject {
protected:
	int id;
public:
	int getID();
};

class Enemy : public Character {
protected:
	int id;
public:
	bool playerIntersection(Player &player);
	int getID();
};

class Swordsman : public Enemy {
public:
	Swordsman(int x, int y);
};

class Fister : public Enemy {
public:
	Fister(int x, int y);
};

class Berserk : public Enemy {
public:
	Berserk(int x, int y);
};
#pragma once

#include "Factory.h"
#include <vector>

class Battle {
private:
	RenderWindow *window;
	View battleView;

	Player* player;
	std::vector <Enemy*> enemies;
	
	double hpModifier;
	bool isAction, isBlocked, exitFlag, inventoryIsOpen, isDead;
	
	Texture menuTexture, cursorTexture, endBattleTexture;
	Sprite menuSprite, cursorSprite, endBattleSprite;
	Vector2f resolution, barSize, hpBarSize, currentPosition;
	Vector2i action;
	RectangleShape *barHitBox, hpBar;

public:
	Battle();
	void create(Player& _player, RenderWindow& _window);
	bool start(Enemy &enemy);
	void endScreen();
	void objectsInitialization(Enemy &enemy);
	void menuInitialization();
	void hpBarInitialization();
	void cursorInitialization();
	void playerInitialization();
	void enemyInitialization(Enemy &enemy);
	void enemyCoordinatesSet();
	void input();
	void attack(Player& attacker, Enemy& defender);
	void attack(Enemy& attacker, Player& defender);
	int chooseEnemy();
	void actionProcessing();
	void defenceUp(Character &defender);
	void defenceDown(Character &defender);
	void draw();
	bool randomGenerator(int probability);
};
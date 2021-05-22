#pragma once

#include "Factory.h"
#include <vector>

class Battle {
private:
	RenderWindow *window;
	View battleView;

	Player player;
	std::vector <Enemy*> enemies;
	
	double hpModifier;
	bool isAction, isBlocked;

	Texture menuTexture, cursorTexture;
	Sprite menuSprite, cursorSprite;
	Vector2f resolution, barSize, hpBarSize, currentPosition;
	Vector2i action;
	RectangleShape *barHitBox, hpBar;

public:
	Battle();
	void create(Player& _player, RenderWindow& _window);
	void start(Enemy enemy);
	void objectsInitialization(Enemy enemy);
	void menuInitialization();
	void hpBarInitialization();
	void cursorInitialization();
	void playerInitialization();
	void enemyInitialization(Enemy enemy);
	void enemyCoordinatesSet();
	void input();
	void attack(Character &attacker, Character &defender, int speedX, int speedY);
	int chooseEnemy();
	void actionProcessing();
	void defenceUp(Character &defender);
	void defenceDown(Character &defender);
	void draw();
	bool randomGenerator(int probability);
};
#pragma once

#include "GameObjects.h"

class EnemyFactory {
public:
	virtual Enemy* createEnemy() = 0;
	virtual ~EnemyFactory() {}
};

class SwordsmanFactory : public EnemyFactory {
public:
	Enemy* createEnemy(int _x, int _y);
};

class FisterFactory : public EnemyFactory {
public:
	Enemy* createEnemy(int _x, int _y);
};

class BerserkFactory : public EnemyFactory {
public:
	Enemy* createEnemy(int _x, int _y);
};
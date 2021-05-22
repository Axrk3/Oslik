#pragma once

#include "GameObjects.h"

class EnemyFactory {
public:
	static Enemy* createEnemy(int x, int y, int id);
	virtual ~EnemyFactory() {}
};

class FriendFactory {
public:
	static Enemy* createFriend(int x, int y, int id);
	virtual ~FriendFactory() {}
};

class ItemFactory {
public:
	static Item* createItem(int x, int y, int id);
	virtual ~ItemFactory() {}
};

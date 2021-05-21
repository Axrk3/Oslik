#pragma once

#include "GameObjects.h"

class EnemyFactory {
public:
	static Enemy* createEnemy(int x, int y, int id);
	virtual ~EnemyFactory() {}
};

class EquipmentFactory {
	static Equipment* createEquipment(int x, int y, int id);
	virtual ~EquipmentFactory() {}
};

class ConsumableFactory {
	static Consumable* createConsumable(int x, int y, int id);
	virtual ~ConsumableFactory() {}
};
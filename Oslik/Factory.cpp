#include "Factory.h"

Enemy* EnemyFactory::createEnemy(int x, int y, int id) {
	Enemy* newEnemy;

	switch (id) {
	case 1:
		newEnemy = new Fister(x, y);
		break;
	case 2:
		newEnemy = new Swordsman(x, y);
		break;
	default:
		newEnemy = new Berserk(x, y);
		break;
	}

	return newEnemy;
}

Equipment* EquipmentFactory::createEquipment(int x, int y, int id) {
	Equipment* newEquipment;

	switch (id)
	{
	case 1:
		newEquipment = new Helmet("Helmet", 3);
		break;
	case 2:
		newEquipment = new Saddle("Saddle", 5);
		break;
	default:
		newEquipment = new Horseshoe("Horseshoe", 2);
		break;
	}

	return newEquipment;
}

Consumable* ConsumableFactory::createConsumable(int x, int y, int id) {
	Consumable* newConsumable;

	switch (id)
	{
	case 1:
		newConsumable = new HealthPotion("HealthPotion", 10);
		break;
	case 2:
		newConsumable = new StrengthPotion("StrengthPotion", 1);
		break;
	default:
		newConsumable = new ResistancePotion("ResistancePotion", 1);
		break;
	}
	
	return newConsumable;
}
#include "Factory.h"

Enemy *EnemyFactory::createEnemy(int x, int y, int id) {
	Enemy *newEnemy;

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

/*Friend* FriendFactory::createFriend(int x, int y, int id) {
	Friend* newFriend;

	switch (id) {
	case 1:
		newFriend = new (x, y);
		break;
	case 2:
		newFriend = new (x, y);
		break;
	default:
		newFriend = new (x, y);
		break;
	}

	return newFriend;
}*/

Item *ItemFactory::createItem(int x, int y, int id) {
	Item *newItem;

	switch (id)
	{
	case 1:
		newItem = new Helmet("Helmet", 3);
		break;
	case 2:
		newItem = new Saddle("Saddle", 5);
		break;
	case 3:
		newItem = new Horseshoe("Horseshoe", 2);
		break;
	case 4:
		newItem = new HealthPotion("HealthPotion", 10);
		break;
	case 5:
		newItem = new StrengthPotion("StrengthPotion", 1);
		break;
	default:
		newItem = new ResistancePotion("ResistancePotion", 1);
		break;
	}

	newItem->hitBox.left = x;
	newItem->hitBox.top = y;
	newItem->sprite.setPosition(x,y);

	return newItem;
}
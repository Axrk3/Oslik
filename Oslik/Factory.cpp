#include "Factory.h"

Enemy* SwordsmanFactory::createEnemy(int _x, int _y) {
	return new Swordsman(_x, _y);
}

Enemy* FisterFactory::createEnemy(int _x, int _y) {
	return new Fister(_x, _y);
}

Enemy* BerserkFactory::createEnemy(int _x, int _y) {
	return new Berserk(_x, _y);
}
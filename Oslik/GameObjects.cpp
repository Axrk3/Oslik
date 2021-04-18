#include "GameObjects.h"
#include <iostream>


void Player::initialize(String fileName,int** &_map, int _blockSize) {
	map = _map;
	blockSize = _blockSize;
	texture.loadFromFile(fileName);
	animation.create("walk", texture, 0, 160, 212, 160, 8, 8, 212);
	animation.create("stay", texture, 0, 0, 210, 160, 8, 5, 210);
	animation.set("stay");
	animation.play();
	// Переделать хитбокс при помощи инициализации и задать спавнпоинт из уровня
	rect = FloatRect(200, 400, 200, 160);
	running = false;
}

void Player::update(float time) {
	rect.left += dx * time;
	collisionX();

	rect.top += dy * time;
	gravity(time);
	collisionY();

	animation.tick(time);

	sprite.setPosition(rect.left,rect.top);
}

void Player::moveLeft(float time) {
	animation.set("walk");
	animation.flip(true);
	dx = -speed;
}

void Player::moveRight(float time) {
	animation.set("walk");
	animation.flip(false);
	dx = speed;
}

void Player::jump() {
	if (onGround) {
		dy = -750;
		onGround = false;
	}
}

void Player::run() {
	if (!running) dx *= 1.5;
	running = true;
}

void Player::stopRun() {
	running = false;
	dx /= 1.5;
}

void Player::stopX() {
	animation.set("stay");
	if (dx > 0) {
		animation.flip(false);
	}
	else {
		animation.flip(true);
	}
	dx = 0;
}

void Player::gravity(float time) {
	dy += g * time;
}

void GameObject::setRect(FloatRect _rect) {
	rect = _rect;
}

void Player::collisionX() {
	for (int i = rect.top / blockSize; i < (rect.top + rect.height) / blockSize; i++) {
		for (int j = rect.left / blockSize; j < (rect.left + rect.width) / blockSize; j++) {
			if (map[i][j] == 0) { 
				continue;
			}
			// От какого-то до такого-то будут физичные блоки
			if ((map[i][j] > 0) && (map[i][j] <= 24)) {

				if (dx > 0) {
					rect.left = j * blockSize - rect.width;
					dx = 0;
				}

				if (dx < 0) {
					rect.left = j * blockSize + blockSize;
					dx = 0;
				}

			}

		}
	}
}

void Player::collisionY() {
	for (int i = rect.top / blockSize; i < (rect.top + rect.height) / blockSize; i++) {
		for (int j = rect.left / blockSize; j < (rect.left + rect.width) / blockSize; j++) {
			if (map[i][j] == 0) {
				continue;
			}
			// От какого-то до такого-то будут физичные блоки
			if ((map[i][j] > 0) && (map[i][j] <= 24)) {

				if (dy > 0) {
					rect.top = i * blockSize - rect.height;
					dy = 0; onGround = true;
				}

				if (dy < 0) {
					rect.top = i * blockSize + blockSize;
					dy = 0;
				}
				
			}
		}
	}
}


/*Player::Player() {
	stats.HP = 85;
	ground = 800;
	texture.loadFromFile("bob.png");
	sprite.setTexture(texture);
	rect = FloatRect(500, ground, 150, 192);
	dy = 0,dx = 0;
}

// id: 0 - x, 1 - y
void GameObject::setRect(int id,int value) {
	if (id == 0) {
		this->rect.left = value;
	} else {
		this->rect.top = value;
	}
}

FloatRect GameObject::getRect() {
	return rect;
}

Sprite GameObject::getSprite() {
	return sprite;
}

void Player::Jump() {
	if (dy == 0) {
		dy = -750;
	}
}

Consumable::Consumable() {
	name = "";
	maxQuantity = 0;
}

Inventory::Inventory() {
	quantityConsum = 0, quantityEquip = 0;
	scale.x = 960; scale.y = 640;
	rect.setSize(scale);
}

void Inventory::addItem(Consumable item, String itemName) {
	this->consum->name = itemName;
	this->consum->maxQuantity++;
}
void Inventory::addItem(Equipment item) {

}*/
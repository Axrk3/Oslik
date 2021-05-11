#include "GameObjects.h"
#include <iostream>


void Player::initialize(String fileName,int** &_map, int _blockSize,Vector2f spawnPoint) {
	map = _map;
	blockSize = _blockSize;
	texture.loadFromFile(fileName);
	animation.create("walk", texture, 0, 160, 212, 160, 8, 8, 212);
	animation.create("stay", texture, 0, 0, 210, 160, 8, 5, 210);
	animation.set("stay");
	animation.play();
	// Переделать хитбокс при помощи инициализации и задать спавнпоинт из уровня
	rect = FloatRect(spawnPoint, Vector2f(200, 160));
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
			if ((map[i][j] > 0) && (map[i][j] <= 200)) {

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
			if ((map[i][j] > 0) && (map[i][j] <= 200)) {

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

/*void Player::openInventory(Window& window) {
	inventory.open(window);
	inventory.input();
}*/

Consumable::Consumable() {
	rect.height = rect.width = 64;
	name = "";
	maxQuantity = 0;
}

Sprite Consumable::getSpriteInInventory() {
	return spriteInInventory;
}

Inventory::Inventory() {
	quantityConsum = 0, quantityEquip = 0;

	texture.loadFromFile("inventory.png");
	sprite.setTexture(texture);
	sprite.setPosition(480, 270);


	attackRect.setPosition(1248, 328);
	attackRect.setFillColor(Color::Red);

	consumable[0].rect.left = 540;
	consumable[0].rect.top = 320;

	consumable[1].rect.left = 640;
	consumable[1].rect.top = 320;

	consumable[2].rect.left = 540;
	consumable[2].rect.top = 420;
	/*for (int i = 0; i < 3; i++) {
		if (i % 2 == 0) {
			items[i].rect.setPosition(540,  320);
		}
	}*/
}

void Inventory::open(RenderWindow& window) {
	RectangleShape r;
	r.setSize(Vector2f(500, 500));
	r.setPosition(Vector2f(100, 100));
	r.setFillColor(Color::White);
	while (true) {
	window.draw(r);
	window.display();
	if (Keyboard::isKeyPressed(Keyboard::C)) break;
	}
}

/*void Inventory::addItem(Consumable& item) {
	for (int i = 0; i < 8; i++) {
		if (items[i].isEmpty) {
			item.rect.left = items[i].rect.left;
			item.rect.top = items[i].rect.top;
			item.spriteInInventory.setPosition(item.rect.left, item.rect.top);
			item.isEmpty = false;
			items[i] = item;
			break;
		}
	}
}*/

void Inventory::addItem(Equipment item) {

}

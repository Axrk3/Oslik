#include "GameObjects.h"
#include <iostream>


void GameObject::setHitBox(FloatRect _hitBox) {
	hitBox = _hitBox;
}

Sprite GameObject::getSprite() {
	return sprite;
}

FloatRect GameObject::getHitBox() {
	return hitBox;
}

Character::characteristics Character::getStats() {
	return stats;
}

void Player::initialize(String fileName,int** &_map, int _blockSize,Vector2f spawnPoint) {
	// ����� �������� � ����������� � ������� ����� ��� ����� �����
	stats.HP = 100;
	stats.ATK = 40;
	stats.DEF = 10;
	map = _map;
	blockSize = _blockSize;
	texture.loadFromFile(fileName);
	animation.create("walk", texture, 0, 160, 212, 160, 8, 8, 212);
	animation.create("stay", texture, 0, 0, 210, 160, 8, 5, 210);
	animation.set("stay");
	animation.play();
	hitBox = FloatRect(spawnPoint, Vector2f(200, 160));
	running = false;
}

void Player::update(float time) {
	hitBox.left += dx * time;
	collisionX();

	hitBox.top += dy * time;
	gravity(time);
	collisionY();

	animation.tick(time);

	sprite.setPosition(hitBox.left, hitBox.top);
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

void Player::collisionX() {
	for (int i = hitBox.top / blockSize; i < (hitBox.top + hitBox.height) / blockSize; i++) {
		for (int j = hitBox.left / blockSize; j < (hitBox.left + hitBox.width) / blockSize; j++) {
			if (map[i][j] == 0) { 
				continue;
			}
			// �� ������-�� �� ������-�� ����� �������� �����
			if ((map[i][j] > 0) && (map[i][j] <= 200)) {

				if (dx > 0) {
					hitBox.left = j * blockSize - hitBox.width;
					dx = 0;
				}

				if (dx < 0) {
					hitBox.left = j * blockSize + blockSize;
					dx = 0;
				}

			}

		}
	}
}

void Player::collisionY() {
	for (int i = hitBox.top / blockSize; i < (hitBox.top + hitBox.height) / blockSize; i++) {
		for (int j = hitBox.left / blockSize; j < (hitBox.left + hitBox.width) / blockSize; j++) {
			if (map[i][j] == 0) {
				continue;
			}
			// �� ������-�� �� ������-�� ����� �������� �����
			if ((map[i][j] > 0) && (map[i][j] <= 200)) {

				if (dy > 0) {
					hitBox.top = i * blockSize - hitBox.height;
					dy = 0; onGround = true;
				}

				if (dy < 0) {
					hitBox.top = i * blockSize + blockSize;
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

Sprite Item::getSpriteInInventory() {
	return spriteInInventory;
}

Inventory::Inventory() {
	quantityConsum = 0, quantityEquip = 0;

	texture.loadFromFile("inventory.png");
	sprite.setTexture(texture);
	sprite.setPosition(480, 270);


	attackBar.setPosition(1248, 328);
	attackBar.setFillColor(Color::Red);

	consumable[0].hitBox.left = 540;
	consumable[0].hitBox.top = 320;

	consumable[1].hitBox.left = 640;
	consumable[1].hitBox.top = 320;

	consumable[2].hitBox.left = 540;
	consumable[2].hitBox.top = 420;
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

int Enemy::getID() {
	return id;
}

Swordsman::Swordsman(int x, int y) {
	hitBox.left = x;
	hitBox.top = y;
	hitBox.width = 150;
	hitBox.height = 192;

	id = 1;

	texture.loadFromFile("Swordsman.png");
	sprite.setTexture(texture);
	sprite.setPosition(hitBox.left, hitBox.top);
}

Fister::Fister(int x, int y) {
	hitBox.left = x;
	hitBox.top = y;
	hitBox.width = 150;
	hitBox.height = 192;

	stats.HP = 50;
	stats.ATK = 20;
	stats.DEF = 5;

	id = 2;

	texture.loadFromFile("Fister.png");
	sprite.setTexture(texture);
	sprite.setPosition(hitBox.left, hitBox.top);
}

Berserk::Berserk(int x, int y) {
	hitBox.left = x;
	hitBox.top = y;

	id = 3;

	texture.loadFromFile("Berserk.png");
	sprite.setTexture(texture);
}
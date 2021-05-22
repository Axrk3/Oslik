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
	// „асть выкинуть в конструктор и сделать метод дл€ смены карты
	stats.HP = 100;
	stats.ATK = 40;
	stats.DEF = 10;
	map = _map;
	blockSize = _blockSize;
	texture.loadFromFile(fileName);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0,0,154,119));
	animation.create("walk", texture, 0, 0, 154, 119, 7, 8, 154);
	//animation.create("stay", texture, 0, 0, 210, 160, 8, 5, 210);
	animation.create("stay", texture, 0, 0, 154, 119, 1, 0, 0);
	animation.set("stay");
	animation.play();
	hitBox = FloatRect(spawnPoint, Vector2f(154, 119));
	running = false;

}

void Player::update(float time,Vector2f viewCenter) {
	hitBox.left += dx * time;
	collisionX();
	
	hitBox.top += dy * time;
	gravity(time);
	collisionY();

	animation.tick(time);
	inventory.update(viewCenter);
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
			// ќт какого-то до такого-то будут физичные блоки
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
			// ќт какого-то до такого-то будут физичные блоки
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

void Player::openInventory(RenderWindow &window) {

}

/*void Engine::drawInventory() {
	window.draw(player.inventory.getSprite());

	for (int i = 0; i < 2; i++) {
		if (!player.inventory.items[i].isEmpty) {
			window.draw(player.inventory.items[i].spriteInInventory);
		}
	}

	Vector2f size;
	size.x = 13 * player.stats.ATK - 2;
	size.y = 25;
	player.inventory.attackRect.setSize(size);
	window.draw(player.inventory.attackRect);
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

void Inventory::update(Vector2f viewCenter) {
	sprite.setPosition(viewCenter.x - 480, viewCenter.y - 270);
}

void Inventory::draw(RenderWindow& window) {
	window.draw(sprite);
	window.draw(attackBar);
	window.draw(hpBar);
	for (int i = 0; i < 8; i++) {
		if (!consumable[i].isEmpty) window.draw(consumable[i].item->getSprite());
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

bool Enemy::playerIntersection(Player &player) {
	if (hitBox.intersects(player.hitBox)) {
		return 1;
	}
	else {
		return 0;
	}
}

int Enemy::getID() {
	return id;
}

Swordsman::Swordsman(int x, int y) {
	hitBox.left = x;
	hitBox.top = y;
	hitBox.width = 150;
	hitBox.height = 192;

	id = 1;

	texture.loadFromFile("Fister.png");
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

	texture.loadFromFile("Fister.png");
	sprite.setTexture(texture);
}
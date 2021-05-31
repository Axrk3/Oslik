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

void Player::openInventory(RenderWindow &window) {

}

Sprite Item::getSpriteInInventory() {
	return spriteInInventory;
}

Inventory::Inventory() {
	quantityConsum = 0, quantityEquip = 0;

	texture.loadFromFile("inventory.png");
	sprite.setTexture(texture);
	sprite.setPosition(480, 270);

	menuTexture.loadFromFile("actionMenu.png");
	menuSprite.setTexture(menuTexture);
	exemineButton.setTexture(menuTexture);
	useButton.setTexture(menuTexture);
	dropButton.setTexture(menuTexture);

	menuSprite.setTextureRect(IntRect(0, 0, 127, 95));
	exemineButton.setTextureRect(IntRect(0, 96, 99, 19));
	useButton.setTextureRect(IntRect(0, 116, 99, 19));
	dropButton.setTextureRect(IntRect(0, 136, 99, 19));

	attackBar.setPosition(1248, 328);
	attackBar.setFillColor(Color::Red);

	for (int i = 0; i < 3; i++) {
		buttons[i].width = 99;
		buttons[i].height = 19;
	}

	for (int i = 0; i < 8; i++) {
		cells[i].hitBox.width = 86;
		cells[i].hitBox.height = 85;
	}

	/*for (int i = 0; i < 3; i++) {
		if (i % 2 == 0) {
			items[i].rect.setPosition(540, 320);
		}
	}*/
}

void Inventory::input() {
	mousePosition.x = sprite.getPosition().x - 1920 / 4 + Mouse::getPosition().x;
	mousePosition.y = sprite.getPosition().y - 1080 / 4 + Mouse::getPosition().y;

	if (Mouse::isButtonPressed(Mouse::Button::Left)) {
		isClicked = false;
	}

	for (int i = 0; i < 8; i++) {
		if (mousePosition.x >= cells[i].hitBox.left && mousePosition.x <= cells[i].hitBox.left + cells[i].hitBox.width &&
			mousePosition.y >= cells[i].hitBox.top && mousePosition.y <= cells[i].hitBox.top + cells[i].hitBox.height) {
			if (Mouse::isButtonPressed(Mouse::Button::Left) ) {
				isClicked = true;
				openedCell = i;
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		if (mousePosition.x >= buttons[i].left && mousePosition.x <= buttons[i].left + buttons[i].width &&
			mousePosition.y >= buttons[i].top && mousePosition.y <= buttons[i].top + buttons[i].height) {
			activeButton = i;
		}
	}
}

void Inventory::draw(RenderWindow &window) {
	window.draw(sprite);
	window.draw(attackBar);
	window.draw(hpBar);
	for (int i = 0; i < 8; i++) {
		if (!cells[i].isEmpty) window.draw(cells[i].item->getSprite());
	}
	
	if (isClicked) {
		window.draw(menuSprite);

		switch (activeButton)
		{
		case 0: 
			exemineButton.setPosition(buttons[0].left, buttons[0].top); //��������� �� ��� �� � ������� 1 ������
			window.draw(exemineButton);
			break;
		case 1:
			useButton.setPosition(buttons[1].left, buttons[1].top);
			window.draw(useButton);
			break;
		case 2:
			dropButton.setPosition(buttons[2].left, buttons[2].top);
			window.draw(dropButton);
			break;
		}
	}
}

void Inventory::update(Vector2f viewCenter) {
	sprite.setPosition(viewCenter.x - 480, viewCenter.y - 270);

	int firstRow = 51, secondRow = 150;
	int yDelimeter = 42;

	for (int i = 0; i < 3; i++) {
		buttons[i].left = menuSprite.getPosition().x + 14;
		buttons[i].top = menuSprite.getPosition().y + 12 + i * 26;
	}

	for (int i = 0; i < 7; i += 2) {
		cells[i].hitBox.left = sprite.getPosition().x + firstRow;
		cells[i + 1].hitBox.left = sprite.getPosition().x + secondRow;
		cells[i].hitBox.top = cells[i + 1].hitBox.top = sprite.getPosition().y + yDelimeter;
		yDelimeter += 96;
 	}

	menuSprite.setPosition(cells[openedCell].hitBox.left + cells[openedCell].hitBox.width, cells[openedCell].hitBox.top);
}

void Inventory::addItem(Item &item) {
	for (int i = 0; i < 8; i++) {
		if (!cells[i].isEmpty) {
			item.sprite.setPosition(cells[i].hitBox.left, cells[i].hitBox.top);
			cells[i].isEmpty = false;
			break;
		}
	}
}

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
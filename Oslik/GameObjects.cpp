#include "GameObjects.h"
#include <fstream>
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

void Character::setStats(characteristics _stats) {
	stats.HP = _stats.HP;
	stats.ATK = _stats.ATK;
	stats.DEF = _stats.DEF;
}

Player::Player(){
	hitBox = FloatRect(Vector2f(0, 0), Vector2f(154, 119));
	animation.create("walk", texture, 0, 0, 154, 119, 7, 8, 154);
	//animation.create("stay", texture, 0, 0, 210, 160, 8, 5, 210);
	animation.create("stay", texture, 0, 0, 154, 119, 1, 0, 0);
	animation.set("stay");
}

void Player::initialize(String fileName, int **&_map) {
	// ����� �������� � ����������� � ������� ����� ��� ����� �����
	stats.HP = 100;
	stats.ATK = 40;
	stats.DEF = 10;

	map = _map;
	blockSize = 64;
	texture.loadFromFile(fileName);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 154, 119));
	animation.play();
	running = false;

}

void Player::update(float time, Vector2f viewCenter) {
	hitBox.left += dx * time;
	collisionX();
	
	hitBox.top += dy * time;
	gravity(time);
	collisionY();

	animation.tick(time);
	inventory.update(this->getStats(), viewCenter);
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

void Player::setSpawnPoint(Vector2f spawnPoint) {
	hitBox.left = spawnPoint.x;
	hitBox.top = spawnPoint.y;
}

void Player::openInventory(RenderWindow &window, Vector2f viewCenter) {
	window.clear(Color::White);
	inventory.input(*this);
	inventory.update(this->getStats(), viewCenter);
	inventory.draw(window);
	window.display();
}

int Friend::getID() {
	return id;
}

Item::Item(String _name, int _coefficient) {
	name = _name;
	coefficient = _coefficient;

	texture.loadFromFile(name + ".png");
	sprite.setTexture(texture);
}

String Item::examine() {
	return discription;
}

bool Item::playerIntersection(Player &player) {
	if (hitBox.intersects(player.hitBox)) {
		return 1;
	}
	else {
		return 0;
	}
}

Sprite Item::getSpriteInInventory() {
	return spriteInInventory;
}

int Item::getID() {
	return id;
}

void HealthPotion::use(Player &player) {
	if (player.stats.HP + coefficient > 100) {
		player.stats.HP = 100;
	}
	else {
		player.stats.HP += coefficient;
	}
}

void StrengthPotion::use(Player& player) {
	if (player.stats.ATK + coefficient > 50) {
		player.stats.ATK = 50;
	}
	else {
		player.stats.ATK += coefficient;
	}
}

void ResistancePotion::use(Player &player) {
	if (player.stats.DEF + coefficient > 50) {
		player.stats.DEF = 50;
	}
	else {
		player.stats.DEF += coefficient;
	}
}

void Helmet::use(Player& player) {

}

void Saddle::use(Player& player) {

}

void Horseshoe::use(Player& player) {

}

Inventory::Inventory() {
	quantityConsum = 0, quantityEquip = 0;

	texture.loadFromFile("inventory.png");
	sprite.setTexture(texture);
	sprite.setPosition(480, 270);

	menuTexture.loadFromFile("actionMenu.png");
	menuSprite.setTexture(menuTexture);
	menuSprite.setTextureRect(IntRect(0, 0, 127, 95));

	buttonSprite.setTexture(menuTexture);
	
	inventoryBars[0].setFillColor(Color(220, 20, 60, 255));
	inventoryBars[1].setFillColor(Color(215, 123, 186, 255));
	inventoryBars[2].setFillColor(Color(99, 155, 255, 255));


	for (int i = 0; i < 3; i++) {
		buttons[i].width = 99;
		buttons[i].height = 19;
	}

	for (int i = 0; i < 8; i++) {
		cells[i].hitBox.width = 67;
		cells[i].hitBox.height = 67;
		cells[i].isEmpty = true;
	}

	for (int i = 0; i < 3; i++) {
		equipmentCells[i].hitBox.width = 67;
		equipmentCells[i].hitBox.height = 67;
		equipmentCells[i].isEmpty = true;
	}

	font.loadFromFile("times.ttf");
	text.setFont(font);
	text.setCharacterSize(28);
	text.setFillColor(Color::Black);
}

void Inventory::input(Player &player) {
	mousePosition.x = sprite.getPosition().x - 480 + Mouse::getPosition().x;
	mousePosition.y = sprite.getPosition().y - 270 + Mouse::getPosition().y;

	if (Mouse::isButtonPressed(Mouse::Button::Left)) {
		isClicked = false;
		isExamine = false;
	}

	for (int i = 0; i < 8; i++) {
		if (mousePosition.x >= cells[i].hitBox.left && mousePosition.x <= cells[i].hitBox.left + cells[i].hitBox.width &&
			mousePosition.y >= cells[i].hitBox.top && mousePosition.y <= cells[i].hitBox.top + cells[i].hitBox.height &&
			activeButton == -1) {
			if (Mouse::isButtonPressed(Mouse::Button::Left) && !cells[i].isEmpty) {
				isClicked = true;
				openedCell = i;
				break;
			}
		}
		else {
			if (Mouse::isButtonPressed(Mouse::Button::Left) && activeButton == -1) {
				openedCell = -1;
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		if (mousePosition.x >= equipmentCells[i].hitBox.left && mousePosition.x <= equipmentCells[i].hitBox.left + equipmentCells[i].hitBox.width &&
			mousePosition.y >= equipmentCells[i].hitBox.top && mousePosition.y <= equipmentCells[i].hitBox.top + equipmentCells[i].hitBox.height &&
			activeButton == -1) {
			if (Mouse::isButtonPressed(Mouse::Button::Left) && !equipmentCells[i].isEmpty) {
				isClicked = true;
				openedEquipmentCell = i;
				break;
			}
		}
		else {
			if (Mouse::isButtonPressed(Mouse::Button::Left) && activeButton == -1) {
				openedEquipmentCell = -1;
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		if (mousePosition.x >= buttons[i].left && mousePosition.x <= buttons[i].left + buttons[i].width &&
			mousePosition.y >= buttons[i].top && mousePosition.y <= buttons[i].top + buttons[i].height) {
			activeButton = i;
			if (Mouse::isButtonPressed(Mouse::Button::Left)) {
				menuLogic(player);
			}
			break;
		}
		else {
			activeButton = -1;
		}
	}
}

void Inventory::menuLogic(Player &player) {
	switch (activeButton)
	{
	case 0:
		if (openedCell > -1) {
			text.setString(cells[openedCell].item->examine());
			isExamine = true;
		}
		if (openedEquipmentCell > -1) {
			text.setString(equipmentCells[openedEquipmentCell].item->examine());
		}
		break;
	case 1:
		if (openedCell > -1) {
			cells[openedCell].item->use(player);
			cells[openedCell].drop();
		}
		if (openedEquipmentCell > -1) {
			addItem(*equipmentCells[openedEquipmentCell].item);
			equipmentCells[openedEquipmentCell].drop();
		}
		break;
	case 2:
		if (openedCell > -1) {
			cells[openedCell].drop();
		}
		if (openedEquipmentCell > -1) {
			cells[openedEquipmentCell].drop();
		}
		break;
	}
}

void Inventory::draw(RenderWindow &window) {
	window.draw(sprite);
	
	for (int i = 0; i < 3; i++) {
		window.draw(inventoryBars[i]);
	}

	for (int i = 0; i < 8; i++) {
		if (!cells[i].isEmpty) {
			window.draw(cells[i].item->getSprite());
		}
	}

	if (isClicked) {
		window.draw(menuSprite);

		if (activeButton > -1) {
			window.draw(buttonSprite);
		}
	}

	if (isExamine) {
		window.draw(text);
	}
}

void Inventory::update(Character::characteristics stats, Vector2f viewCenter) {
	sprite.setPosition(viewCenter.x - 480, viewCenter.y - 270);
	menuSprite.setPosition(cells[openedCell].hitBox.left + cells[openedCell].hitBox.width, cells[openedCell].hitBox.top);
	text.setPosition(sprite.getPosition().x + 285, sprite.getPosition().y + 365);

	updateBars(stats);
	updateItemsIcons();
	updateButtons();
	updateCells();
}

void Inventory::updateCells() {
	int first�olumn = 61, second�olumn = 160, yDelimeter = 51;
	for (int i = 0; i < 7; i += 2) {
		cells[i].hitBox.left = sprite.getPosition().x + first�olumn;
		cells[i + 1].hitBox.left = sprite.getPosition().x + second�olumn;
		cells[i].hitBox.top = cells[i + 1].hitBox.top = sprite.getPosition().y + yDelimeter;
		yDelimeter += 96;
	}
}

void Inventory::updateEquipmentCells() {
	equipmentCells[0].hitBox.left = sprite.getPosition().x + 568;
	equipmentCells[0].hitBox.top = sprite.getPosition().y + 86;
	equipmentCells[1].hitBox.left = sprite.getPosition().x + 413;
	equipmentCells[1].hitBox.top = sprite.getPosition().y + 91;
	equipmentCells[2].hitBox.left = sprite.getPosition().x + 476;
	equipmentCells[2].hitBox.top = sprite.getPosition().y + 229;
}

void Inventory::updateBars(Character::characteristics stats) {
	int x = 768, yDelimeter = 58, step = 48;
	for (int i = 0; i < 3; i++) {
		inventoryBars[i].setPosition(sprite.getPosition().x + x, sprite.getPosition().y + yDelimeter);
		yDelimeter += step;
	}

	inventoryBars[0].setSize(Vector2f(1.28 * stats.HP, 25));
	inventoryBars[1].setSize(Vector2f(2.56 * stats.ATK, 25));
	inventoryBars[2].setSize(Vector2f(2.56 * stats.DEF, 25));
}

void Inventory::updateItemsIcons() {
	for (int i = 0; i < 8; i++) {
		if (!cells[i].isEmpty) {
			cells[i].item->sprite.setPosition(cells[i].hitBox.left, cells[i].hitBox.top);
		}
	}
}

void Inventory::updateButtons() {
	int x = 14, yDelimeter = 12, step = 26;

	for (int i = 0; i < 3; i++) {
		if (isClicked) {
			buttons[i].left = menuSprite.getPosition().x + x;
			buttons[i].top = menuSprite.getPosition().y + yDelimeter;
			yDelimeter += step;
		}
		else {
			buttons[i].left = 0;
			buttons[i].top = 0;
		}
	}

	switch (activeButton)
	{
	case 0:
		buttonSprite.setTextureRect(IntRect(0, 96, 99, 19));
		buttonSprite.setPosition(buttons[0].left, buttons[0].top);
		break;
	case 1:
		buttonSprite.setTextureRect(IntRect(0, 116, 99, 19));
		buttonSprite.setPosition(buttons[1].left, buttons[1].top);
		break;
	case 2:
		buttonSprite.setTextureRect(IntRect(0, 136, 99, 19));
		buttonSprite.setPosition(buttons[2].left, buttons[2].top);
		break;
	}
}

void Inventory::addItem(Item &item) {
	for (int i = 0; i < 8; i++) {
		if (cells[i].isEmpty) {
			cells[i].item = &item;
			cells[i].isEmpty = false;
			break;
		}
	}
}

void Inventory::addItem(Item &item, int index) {
	cells[index].item = &item;
	cells[index].isEmpty = false;
}

void Inventory::clear() {
	for (int i = 0; i < 8; i++) {
		cells[i].drop();
	}
}

void Cell::drop() {
	delete item;
	item = 0;
	isEmpty = true;
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

Fister::Fister(int x, int y) {
	hitBox.left = x;
	hitBox.top = y;
	hitBox.width = 150;
	hitBox.height = 192;

	stats.HP = 50;
	stats.ATK = 20;
	stats.DEF = 5;

	id = 1;

	texture.loadFromFile("Fister.png");
	sprite.setTexture(texture);
	sprite.setPosition(hitBox.left, hitBox.top);
}

Swordsman::Swordsman(int x, int y) {
	hitBox.left = x;
	hitBox.top = y;
	hitBox.width = 150;
	hitBox.height = 192;

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
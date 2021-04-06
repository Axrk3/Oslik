#include "GameObjects.h"
#include "PlayerCollisions.h"
#include <iostream>


void Player::initialize(String fileName,Level &_lvl) {
	lvl = _lvl;
	texture.loadFromFile(fileName);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(43, 13, 73, 50));
	//sprite.setScale(2,2);
	rect = FloatRect(lvl.spawnPoint.x, lvl.spawnPoint.y,  73,  50);
}

void Player::update(float time) {
	rect.left += dx * time;
	collisionX(lvl.map,rect,dx,lvl.blockSize);

	rect.top += dy * time;
	gravity(time);
	collisionY(lvl.map,rect,dy,onGround,lvl.blockSize);

	// animation.tick(time);

	sprite.setPosition(rect.left,rect.top);
}

void Player::moveLeft(float time) {
	dx = -speed;
}

void Player::moveRight(float time) {
	dx = speed;
}

void Player::jump() {
	if (onGround) {
		dy = -750;
		onGround = false;
	}
}

void Player::run() {
	dx *= 1.5;
}

void Player::stopRun() {
	dx /= 1.5;
}

void Player::stopX() {
	dx = 0;
}

void Player::gravity(float time) {
	dy += g * time;
}

void GameObject::setRect(FloatRect _rect) {
	rect = _rect;
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
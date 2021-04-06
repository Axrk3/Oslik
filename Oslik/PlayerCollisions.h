#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

void collisionX(int** map,FloatRect &hitBox, int &dx, int blockSize) {
	for (int i = hitBox.top / blockSize; i < (hitBox.top + hitBox.height) / blockSize; i++) {
		for (int j = hitBox.left / blockSize; j < (hitBox.left + hitBox.width) / blockSize; j++) {
			if (map[i][j] == 0) continue;
			// Физичные объекты расположим в ряд от одного числа до другого
			if ((map[i][j] > 0) && (map[i][j] <= 24)) {

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

void collisionY(int** map, FloatRect& hitBox, int& dy,bool &onGround, int blockSize) {
	for (int i = hitBox.top / blockSize; i < (hitBox.top + hitBox.height) / blockSize; i++) {
		for (int j = hitBox.left / blockSize; j < (hitBox.left + hitBox.width) / blockSize; j++) {
			if (map[i][j] == 0) continue;
			// Физичные объекты расположим в ряд от одного числа до другого
			if ((map[i][j] > 0) && (map[i][j] <= 24)) {

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
#pragma once

#include <SFML/Graphics.hpp>
#include "GameObjects.h"
#include "Level.h"
#include <iostream>
#include <string>

using namespace sf;

class Engine {
public:
	RenderWindow window;
	Vector2f resolution;
	Sprite backgroundSprite;
	Texture backgroundTexture;
	View view;
	Level lvl;
	Player player;
	int offsetX, offsetY;
public:
	Engine();
	void input(Event event, float time);
	void draw();
	void update(float time);
	void offset();
	void start();
};


#pragma once

#include <SFML/Graphics.hpp>
#include "GameObjects.h"
#include "Level.h"
#include <iostream>
#include <string>
#include "Menu.h"

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
	Clock clock;
	GameMenu menu;
	int offsetX, offsetY;
	float time;
	bool menuIsOpen = false;
public:
	Engine();
	void input(Event event, float time);
	void draw();
	void update(float time);
	void offset();
	void start();
};


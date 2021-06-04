#pragma once

#include <SFML/Graphics.hpp>
#include "GameObjects.h"
#include "Level.h"
#include "Battle.h"
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
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
	MainMenu mainMenu;
	Event event;
	SoundBuffer InventoryBuffer;
	Sound InventorySound;
	bool clearEventPoll;

	int offsetX, offsetY, gameMenuChoice;
	float time;
	bool menuIsOpen = false, inventoryIsOpen, closeGame = false;
	void initialization();
	void input(Event event, float time);
	void draw();
	void update(float time);
	void offset();
	int invokeGameMenu();
	void loading();
	void closeSession();
	void drawInventory();
	void makeSave();
public:
	Engine();
	void start();
	int startMainMenu();
};


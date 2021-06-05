#pragma once

#include <SFML/Graphics.hpp>
#include "GameObjects.h"
#include "Level.h"
#include "Battle.h"
#include <iostream>
#include <string>
#include "Menu.h"

using namespace sf;

class Engine {
private:
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
	SoundBuffer inventorySoundBuffer;
	Sound sound;
	bool clearEventPoll;

	int offsetX, offsetY, gameMenuChoice, outcome;
	float time;
	bool menuIsOpen = false, inventoryIsOpen, closeGame = false;
	void initialization(String fileName);
	void input(Event event, float time);
	void draw();
	void update(float time);
	void offset();
	int invokeGameMenu();
	void loading();
	void closeSession();
	void drawInventory();
	void makeSave();
	void outcomeProcessing();
public:
	Engine();
	void start(String fileName);
	int startMainMenu();
};


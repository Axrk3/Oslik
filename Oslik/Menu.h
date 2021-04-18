#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Menu {
protected:
	Vector2f menuSize, menuBarSize, mousePosition, menuPosition;
	RectangleShape menu, * menuBar;
	int menuBarNum, currentBar = 0;
	bool closeMenu = false;
	Font font;
	Text* text;

	virtual void menuInput() = 0;
	virtual void menuLogic() = 0;

public:
	virtual void initializeMenu(Vector2f _menuSize, Vector2f _menuBarSize) = 0;
	virtual void drawMenu(RenderWindow& window, Vector2f menuPosition) = 0;
};

class GameMenu : public Menu {
protected:
	void menuInput();
	void menuLogic();

public:
	void initializeMenu(Vector2f _menuSize, Vector2f _menuBarSize);
	void drawMenu(RenderWindow& window,Vector2f menuPosition);
	void updateMenu(Vector2f _menuPosition);
};

/*class MainMenu : public Menu {
protected:
	void menuInput();
	void menuLogic();

public:
	void initializeMenu(Vector2f _menuSize, Vector2f _menuBarSize, Vector2f _menuPosition, int menuBarNum);
	void drawMenu(RenderWindow& window);
};*/
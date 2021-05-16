#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Menu {
protected:
	Vector2f menuSize, menuBarSize, mousePosition, Offset, menuPosition;
	RectangleShape menu, * menuBar;
	int menuBarNum, currentBar = 0;
	Font font;
	Text* text;

	virtual void menuInput() = 0;
	virtual void menuLogic() = 0;
	virtual void drawMenu(RenderWindow& window) = 0;

public:
	// Временно флаг тут, переделать
	bool closeMenu = false;
	virtual void initializeMenu(Vector2f _menuSize, Vector2f _menuBarSize) = 0;
	virtual int invokeMenu(RenderWindow& window) = 0;
};

class GameMenu : public Menu {
protected:
	void menuInput();
	void menuLogic();
	void drawMenu(RenderWindow& window);
public:
	void initializeMenu(Vector2f _menuSize, Vector2f _menuBarSize);
	int invokeMenu(RenderWindow& window);
	void updateMenu(Vector2f _menuPosition);
};

class MainMenu : public Menu {
protected:
	int choice = 0;

	void menuInput();
	void menuLogic();
	void drawMenu(RenderWindow& window);
public:
	void initializeMenu(Vector2f _menuSize, Vector2f _menuBarSize);
	int invokeMenu(RenderWindow& window);
};
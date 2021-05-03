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

public:
	// �������� ���� ���
	bool closeMenu = false;
	virtual void initializeMenu(Vector2f _menuSize, Vector2f _menuBarSize) = 0;
	virtual void drawMenu(RenderWindow& window, Vector2f menuPosition) = 0;
};

class GameMenu : public Menu {
protected:
	void menuInput();
	void menuLogic();
public:
	// ��� �������� ����
	bool Flag;
	//...
	void initializeMenu(Vector2f _menuSize, Vector2f _menuBarSize);
	void drawMenu(RenderWindow& window,Vector2f menuPosition);
	void updateMenu(Vector2f _menuPosition);
};

class MainMenu : public Menu {
protected:
	void menuInput();
	void menuLogic();
public:
	void initializeMenu(Vector2f _menuSize, Vector2f _menuBarSize);
	void drawMenu(RenderWindow& window, Vector2f menuPosition);
};
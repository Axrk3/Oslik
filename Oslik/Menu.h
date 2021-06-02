#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Menu {
protected:
	Vector2f mousePosition;
	int activeButton = -1;

	Texture menuTexture;
	Sprite menuSprite, buttonSprite;
	FloatRect *buttons;

	virtual void menuInput() = 0;
	virtual void menuLogic() = 0;
	virtual void drawMenu(RenderWindow& window) = 0;

public:
	virtual int invokeMenu(RenderWindow &window) = 0;
};

class GameMenu : public Menu {
protected:
	void menuInput();
	void menuLogic();
	void drawMenu(RenderWindow &window);
	bool closeMenu = false, closeGame = false, makeSave = false;
public:
	GameMenu();
	int invokeMenu(RenderWindow &window);
	void updateMenu(Vector2f viewCenter);
};

class MainMenu : public Menu {
protected:
	int choice = 0;
	Sprite background;

	void menuInput();
	void menuLogic();
	void drawMenu(RenderWindow &window);
public:
	MainMenu();
	int invokeMenu(RenderWindow &window);
};
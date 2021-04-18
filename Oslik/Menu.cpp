#include "Menu.h"


void GameMenu::initializeMenu(Vector2f _menuSize, Vector2f _menuBarSize) {
	menuSize = _menuSize;
	menuBarSize = _menuBarSize;
	menuBarNum = 2;
	menuPosition = Vector2f(0,0);
	// Тут будет текстура
	menu.setFillColor(Color::Cyan);
	menu.setPosition(menuPosition);
	menu.setSize(menuSize);
	menuBar = new RectangleShape[menuBarNum];
	font.loadFromFile("times.ttf");
	text = new Text[menuBarNum];
	for (int i = 0; i < menuBarNum; i++) {
		menuBar[i].setFillColor(Color::Green);
		menuBar[i].setSize(menuBarSize);
		menuBar[i].setPosition(menu.getPosition().x, i * menuBar->getSize().y + menu.getPosition().y);
		text[i].setFont(font);
		text[i].setCharacterSize(16);
		text[i].setFillColor(Color::Black);
		text[i].setPosition(menuBar[i].getPosition().x + 10, menuBar[i].getPosition().y + 5);
	}
	text[0].setString("RESUME");
	text[1].setString("EXIT");
}

void GameMenu::menuInput() {
	mousePosition = (Vector2f) Mouse::getPosition();
	for (int i = 0; i < menuBarNum; i++) {
		if (mousePosition.x >= menuBar[i].getPosition().x && mousePosition.x <= menuBar[i].getPosition().x + menuBarSize.x &&
			mousePosition.y >= menuBar[i].getPosition().y && mousePosition.y <= menuBar[i].getPosition().y + menuBarSize.y) {
			menuBar[i].setFillColor(Color::Red);
			if (Mouse::isButtonPressed(Mouse::Button::Left)) menuBar[i].setFillColor(Color::Magenta);
		}
		else if (menuBar[i].getFillColor() != Color::Green) menuBar[i].setFillColor(Color::Green);
	}

	/*
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		menuBar[currentBar].setFillColor(Color::Green);
		currentBar--;
		if (currentBar < 0) currentBar = menuBarNum - 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		menuBar[currentBar].setFillColor(Color::Green);
		currentBar++;
		if (currentBar == menuBarNum) currentBar = 0;
	}
	menuBar[currentBar].setFillColor(Color::Red);
	*/
}

// Костыль! Переделать
void GameMenu::menuLogic() {

	if (menuBar[0].getFillColor() == Color::Magenta) {
		closeMenu = true;
	}
	
	if (menuBar[1].getFillColor() == Color::Magenta) {
		exit(1);
	}
}

void GameMenu::drawMenu(RenderWindow &window,Vector2f menuPosition) {
	updateMenu(menuPosition);
	while (true) {
		menuInput();
		menuLogic();
		window.draw(menu);
		for (int i = 0; i < menuBarNum; i++) {
			window.draw(menuBar[i]);
			window.draw(text[i]);
		}
		window.display();
		if (closeMenu) {
			closeMenu = false;
			break;
		}
	}
}

void GameMenu::updateMenu(Vector2f _menuPosition) {

	menu.setPosition(_menuPosition);
	for (int i = 0; i < menuBarNum; i++) {
		menuBar[i].setPosition(menu.getPosition().x, i * menuBarSize.y + menu.getPosition().y);
		text[i].setPosition(menuBar[i].getPosition().x + 10, menuBar[i].getPosition().y + 5);
	}
}

#include "Menu.h"

void GameMenu::initializeMenu(Vector2f _menuSize, Vector2f _menuBarSize) {
	menuSize = _menuSize;
	menuBarSize = _menuBarSize;
	menuBarNum = 2;
	menuPosition = Vector2f(0,0);
	// Тут будет текстура, текст убрать
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
	mousePosition.x = menu.getPosition().x - 1920 / 2 + Mouse::getPosition().x;
	mousePosition.y = menu.getPosition().y - 1080 / 2 + Mouse::getPosition().y;

	for (int i = 0; i < menuBarNum; i++) {
		if (mousePosition.x >= menuBar[i].getPosition().x && mousePosition.x <= menuBar[i].getPosition().x + menuBarSize.x &&
			mousePosition.y >= menuBar[i].getPosition().y && mousePosition.y <= menuBar[i].getPosition().y + menuBarSize.y) {
			menuBar[i].setFillColor(Color::Red);
			if (Mouse::isButtonPressed(Mouse::Button::Left)) menuBar[i].setFillColor(Color::Magenta);
		}
		else if (menuBar[i].getFillColor() != Color::Green) menuBar[i].setFillColor(Color::Green);
	}
	
}

// Костыль! Переделать
void GameMenu::menuLogic() {

	if (menuBar[0].getFillColor() == Color::Magenta) {
		closeMenu = true;
	}
	
	if (menuBar[1].getFillColor() == Color::Magenta) {
		closeGame = true;
	}
}

void GameMenu::drawMenu(RenderWindow& window) {
	// Заменить на текстуры
	window.draw(menu);
	for (int i = 0; i < menuBarNum; i++) {
		window.draw(menuBar[i]);
		window.draw(text[i]);
	}
	window.display();
}

int GameMenu::invokeMenu(RenderWindow &window) {
	while (true) {
		menuInput();
		menuLogic();
		if (closeMenu) {
			closeMenu = false;
			return false;
		}
		if (closeGame) {
			closeGame = false;
			return true;
		}
		drawMenu(window);
	}
}

void GameMenu::updateMenu(Vector2f _menuPosition) {
	// Заменить на текстуры
	menu.setPosition(_menuPosition);
	for (int i = 0; i < menuBarNum; i++) {
		menuBar[i].setPosition(_menuPosition.x, i * menuBarSize.y + _menuPosition.y);
		text[i].setPosition(menuBar[i].getPosition().x + 10, menuBar[i].getPosition().y + 5);
	}
}

void MainMenu::menuInput() {
	mousePosition.x = Mouse::getPosition().x;
	mousePosition.y = Mouse::getPosition().y;

	for (int i = 0; i < menuBarNum; i++) {
		if (mousePosition.x >= menuBar[i].getPosition().x && mousePosition.x <= menuBar[i].getPosition().x + menuBarSize.x &&
			mousePosition.y >= menuBar[i].getPosition().y && mousePosition.y <= menuBar[i].getPosition().y + menuBarSize.y) {
			menuBar[i].setFillColor(Color::Red);
			if (Mouse::isButtonPressed(Mouse::Button::Left)) menuBar[i].setFillColor(Color::Magenta);
		}
		else if (menuBar[i].getFillColor() != Color::Green) menuBar[i].setFillColor(Color::Green);
	}
}

void MainMenu::menuLogic() {
	// Доделать
	if (menuBar[0].getFillColor() == Color::Magenta) {
		choice = 1;
	}

	if (menuBar[1].getFillColor() == Color::Magenta) {
		exit(1);
	}

}

void MainMenu::drawMenu(RenderWindow& window) {
	// Заменить на текстуры
	window.clear(Color::White);
	window.draw(menu);
	for (int i = 0; i < menuBarNum; i++) {
		window.draw(menuBar[i]);
		window.draw(text[i]);
	}
	window.display();
}

void MainMenu::initializeMenu(Vector2f _menuSize, Vector2f _menuBarSize) {
	menuSize = _menuSize;
	menuBarSize = _menuBarSize;
	menuBarNum = 2;
	menuPosition = Vector2f(0, 0);
	// Тут будет текстура, текст убрать
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
	text[0].setString("START");
	// Надо бы добавить поле с сейвами...
	text[1].setString("EXIT");
}

int MainMenu::invokeMenu(RenderWindow& window) {
	// Доделать
	choice = 0;
	while (true) {
		menuInput();
		menuLogic();
		if (choice) {
			return choice;
			break;
		}
		drawMenu(window);
	}
}
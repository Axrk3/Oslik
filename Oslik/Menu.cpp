#include "Menu.h"
#include <iostream>

GameMenu::GameMenu() {
	menuTexture.loadFromFile("gameMenu.png");
	menuSprite.setTexture(menuTexture);
	menuSprite.setTextureRect(IntRect(0, 0, 768, 840));
	menuSprite.setPosition(576, 120);

	buttonSprite.setTexture(menuTexture);

	buttons = new FloatRect[3];
	for (int i = 0; i < 3; i++) {
		buttons[i].width = 512;
		buttons[i].height = 144;
	}
}

void GameMenu::menuInput() {
	mousePosition.x = menuSprite.getPosition().x - 576 + Mouse::getPosition().x;
	mousePosition.y = menuSprite.getPosition().y - 120 + Mouse::getPosition().y;

	for (int i = 0; i < 3; i++) {
		if (mousePosition.x >= buttons[i].left && mousePosition.x <= buttons[i].left + buttons[i].width &&
			mousePosition.y >= buttons[i].top && mousePosition.y <= buttons[i].top + buttons[i].height) {
			activeButton = i;
			if (Mouse::isButtonPressed(Mouse::Button::Left)) {
				menuLogic();
			}
			break;
		}
		else {
			activeButton = -1;
		}
	}

	switch (activeButton)
	{
	case 0:
		buttonSprite.setTextureRect(IntRect(0, 840, 512, 144));
		buttonSprite.setPosition(buttons[0].left, buttons[0].top);
		break;
	case 1:
		buttonSprite.setTextureRect(IntRect(0, 984, 512, 144));
		buttonSprite.setPosition(buttons[1].left, buttons[1].top);
		break;
	case 2:
		buttonSprite.setTextureRect(IntRect(0, 1128, 512, 144));
		buttonSprite.setPosition(buttons[2].left, buttons[2].top);
		break;
	}
}

// Костыль! Переделать
void GameMenu::menuLogic() {
	
}

void GameMenu::drawMenu(RenderWindow &window) {
	window.draw(menuSprite);
	if (activeButton > -1) window.draw(buttonSprite);
	window.display();
}

int GameMenu::invokeMenu(RenderWindow &window) {
	//good jopa
	while (true) {
		menuInput();
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

void GameMenu::updateMenu(Vector2f viewCenter) {
	menuSprite.setPosition(viewCenter.x - 384, viewCenter.y - 420);
	
	int yDelimeter = 112;
	for (int i = 0; i < 3; i++) {
		buttons[i].left = menuSprite.getPosition().x + 128;
		buttons[i].top = menuSprite.getPosition().y + yDelimeter;
		yDelimeter += 256;
	}
}

MainMenu::MainMenu() {
	menuTexture.loadFromFile("mainMenu.png");
	menuSprite.setTexture(menuTexture);
	menuSprite.setTextureRect(IntRect(0, 0, 704, 800));
	menuSprite.setPosition(608, 140);

	buttonSprite.setTexture(menuTexture);

	buttons = new FloatRect[2];
	for (int i = 0; i < 2; i++) {
		buttons[i].width = 512;
		buttons[i].height = 144;
	}

	buttons[0].left = menuSprite.getPosition().x + 96;
	buttons[0].top = menuSprite.getPosition().y + 144;
	buttons[1].left = menuSprite.getPosition().x + 96;
	buttons[1].top = menuSprite.getPosition().y + 536;
}

void MainMenu::menuInput() {
	mousePosition.x = Mouse::getPosition().x;
	mousePosition.y = Mouse::getPosition().y;

	for (int i = 0; i < 2; i++) {
		if (mousePosition.x >= buttons[i].left && mousePosition.x <= buttons[i].left + buttons[i].width &&
			mousePosition.y >= buttons[i].top && mousePosition.y <= buttons[i].top + buttons[i].height) {
			activeButton = i;
			if (Mouse::isButtonPressed(Mouse::Button::Left)) {
				menuLogic();
			}
			break;
		}
		else activeButton = -1;
	}
}

void MainMenu::menuLogic() {
	switch (activeButton)
	{
	case 0: 
		//saveMenu.invokeSaveMenu();
		choice = 1;
		break;
	case 1:
		exit(0);
		break;
	}

}

void MainMenu::drawMenu(RenderWindow &window) {
	window.clear(Color::White);
	window.draw(menuSprite);

	switch (activeButton)
	{
	case 0:
		buttonSprite.setTextureRect(IntRect(0, 800, 512, 144));
		buttonSprite.setPosition(buttons[0].left, buttons[0].top);
		break;
	case 1:
		buttonSprite.setTextureRect(IntRect(0, 944, 512, 144));
		buttonSprite.setPosition(buttons[1].left, buttons[1].top);
		break;
	}

	if (activeButton > -1)
		window.draw(buttonSprite);

	window.display();
}

int MainMenu::invokeMenu(RenderWindow &window) {
	choice = 0;

	while (true) {
		menuInput();
		if (choice) {
			return choice;
			break;
		}
		drawMenu(window);
	}
}
#include "Engine.h"

Engine::Engine() {
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	window.create(VideoMode(resolution.x, resolution.y), "OslikTheGame v0.9", Style::Fullscreen);
	window.setFramerateLimit(60);

	view.reset(FloatRect(0, 0, resolution.x, resolution.y));
}

void Engine::initialization() {
	window.setMouseCursorVisible(false);
	offsetX = resolution.x / 2;
	offsetY = resolution.y / 2;
	lvl.loadLVL(std::string("maps/lvl.txt"), player, window);
	player.initialize("run.png", lvl.map, lvl.blockSize, lvl.spawnPoint);

	update(0);
	draw();
	sleep(milliseconds(100));
	clock.restart();
}

void Engine::input(Event event, float time) {
	if (inventoryIsOpen) {
		player.inventory.input();
	}

	if (event.type == Event::KeyPressed) {

		if (event.key.code == (Keyboard::Escape)) {
			menuIsOpen = true;
			window.setMouseCursorVisible(menuIsOpen);
		}

		if (event.key.code == (Keyboard::A)) {
			player.moveLeft(time);
		}

		if (event.key.code == (Keyboard::D)) {
			player.moveRight(time);
		}

		if (event.key.code == (Keyboard::LShift)) {
			player.run();
		}

		if (event.key.code == (Keyboard::W)) {
			player.jump();
		}

		if (event.key.code == (Keyboard::I)) {
			inventoryIsOpen = !inventoryIsOpen;
			window.setMouseCursorVisible(inventoryIsOpen);
		}
	}

	else if (event.type == Event::KeyReleased) {

		if ((!Keyboard::isKeyPressed(Keyboard::D)) && !(Keyboard::isKeyPressed(Keyboard::A))) {
			player.stopX();
		}

		if (event.key.code == (Keyboard::LShift) && !Keyboard::isKeyPressed(Keyboard::LShift)) {
			player.stopRun();
		}		

		if (event.key.code == (Keyboard::D) && Keyboard::isKeyPressed(Keyboard::A)) player.moveLeft(time);
		
		if (event.key.code == (Keyboard::A) && Keyboard::isKeyPressed(Keyboard::D)) player.moveRight(time);
	}
}

void Engine::draw() {
	window.clear(Color::White);
	window.setView(view);
	lvl.draw(window);
	player.animation.draw(window, player.hitBox.left, player.hitBox.top);
	drawInventory();
	window.display();
}

void Engine::drawInventory() {
	if (inventoryIsOpen) {
		player.inventory.draw(window);
		player.inventory.update(view.getCenter());
	}
}

void Engine::update(float time) {
	lvl.worldUpdate(player, clock, view.getCenter());
	player.update(time, view.getCenter());
	offset();
	view.setCenter(offsetX, offsetY);
	menu.updateMenu(view.getCenter());
}

void Engine::offset() {
	if ((player.hitBox.left > resolution.x / 2) && (player.hitBox.left < lvl.mapSize.x * lvl.blockSize - resolution.x / 2)) {
		offsetX = player.hitBox.left;
	}

	if ((player.hitBox.top > resolution.y / 2) && (player.hitBox.top < lvl.mapSize.y * lvl.blockSize - resolution.y / 2)) {
		offsetY = player.hitBox.top;
	}
}

int Engine::invokeGameMenu() {
	gameMenuChoice = 1;
	if (menuIsOpen) {
		window.setMouseCursorVisible(true);
		menuIsOpen = false;
		switch (menu.invokeMenu(window)) {
		case 0:
			gameMenuChoice = 1;
			break;
		case 1:
			//makeSave();
			break;
		case 2:
			gameMenuChoice = 0;
			break;
		}
		window.setMouseCursorVisible(false);
		clock.restart();
	}
	return gameMenuChoice;
}

void Engine::start() {
	initialization();
	while (true) {
		time = clock.getElapsedTime().asSeconds();
		clock.restart();
		Event event;
		while (window.pollEvent(event)) {
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;

			default:
				input(event, time);
				break;
			}
		}
		if (invokeGameMenu() == 0) break;
		update(time);
		draw();
	}
	closeSession();
}

int Engine::startMainMenu() {
	window.setMouseCursorVisible(true);
	return mainMenu.invokeMenu(window);
}

void Engine::closeSession() {
	view.reset(FloatRect(0, 0, resolution.x, resolution.y));
	window.setView(view);
	lvl.clear();
	sleep(milliseconds(100));
}

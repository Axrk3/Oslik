#include "Engine.h"

Engine::Engine() {
	inventorySoundBuffer.loadFromFile("openInventory.ogg");
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	window.create(VideoMode(resolution.x, resolution.y), "OslikTheGame v0.9", Style::Fullscreen);
	window.setFramerateLimit(120);

	view.reset(FloatRect(0, 0, resolution.x, resolution.y));
}

void Engine::initialization(String fileName) {
	window.setMouseCursorVisible(false);
	offsetX = resolution.x / 2;
	offsetY = resolution.y / 2;
	//Переместить в другое место
	lvl.loadLVL(std::string(fileName), player, window);
	player.initialize("run.png", lvl.map);
	//offset();
	//view.reset(FloatRect(offsetX - resolution.x / 2, offsetY - resolution.y / 2, resolution.x, resolution.y));
	//view.setCenter(offsetX, offsetY);
	//window.setView(view);
	//
	update(0);
	draw();
	sleep(milliseconds(200));
	clock.restart();
}

void Engine::input(Event event, float time) {
	if (clearEventPoll) {
		while (window.pollEvent(event));
		clearEventPoll = false;
		player.stopX();
	}

	if (inventoryIsOpen) {
		player.inventory.input(player);
	}

	if (event.type == Event::KeyPressed) {
		switch (event.key.code)
		{
		case Keyboard::Escape:
			menuIsOpen = true;
			window.setMouseCursorVisible(menuIsOpen);
			break;
		case Keyboard::A:
			player.moveLeft(time);
			break;
		case Keyboard::D:
			player.moveRight(time);
			break;
		case Keyboard::LShift:
			player.run();
			break;
		case Keyboard::W:
			player.jump();
			break;
		case Keyboard::I:
			sound.setBuffer(inventorySoundBuffer);
			sound.play();
			inventoryIsOpen = !inventoryIsOpen;
			window.setMouseCursorVisible(inventoryIsOpen);
			break;
		}
	}

	else if (event.type == Event::KeyReleased) {
		switch (event.key.code)
		{
		case Keyboard::D:
		case Keyboard::A:
			player.stopX();
			if (Keyboard::isKeyPressed(Keyboard::A)) player.moveLeft(time);
			if (Keyboard::isKeyPressed(Keyboard::D)) player.moveRight(time);
			break;
		case Keyboard::LShift:
			player.stopRun();
			break;
		}
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
		player.inventory.update(player.getStats(), view.getCenter());
	}
}

void Engine::update(float time) {
	outcome = lvl.worldUpdate(player, clock, view.getCenter(), clearEventPoll);
	player.update(time, view.getCenter());
	offset();
	view.setCenter(offsetX, offsetY);
	menu.updateMenu(view.getCenter());
}

void Engine::offset() {
	if ((player.getHitBox().left > resolution.x / 2) && (player.getHitBox().left < lvl.mapSize.x * lvl.blockSize - resolution.x / 2)) {
		offsetX = player.hitBox.left;
	} else {
		offsetX = player.getHitBox().left < resolution.x / 2 ? resolution.x / 2 : lvl.mapSize.x * lvl.blockSize - resolution.x / 2;
	}

	if ((player.getHitBox().top > resolution.y / 2) && (player.getHitBox().top < lvl.mapSize.y * lvl.blockSize - resolution.y / 2)) {
		offsetY = player.hitBox.top;
	} else {
		offsetY = player.getHitBox().top < resolution.y / 2 ? resolution.y / 2 : lvl.mapSize.y * lvl.blockSize - resolution.y / 2;
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
			lvl.makeSave("maps/saveFile.txt", player);
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

void Engine::start(String fileName) {
	initialization(fileName);
	while (true) {
		time = clock.getElapsedTime().asSeconds();
		clock.restart();
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
		if (outcome == 1) {
			break;
		}
		if (outcome == 2) {
			outcomeProcessing();
		}
		draw();
	}
	closeSession();
}

void Engine::outcomeProcessing() {
	lvl.clear();
	int lvlNum = lvl.lvlNum + 1;
	std::string lvlName = "maps/lvl" + std::to_string(lvlNum) + ".txt";
	lvl.loadLVL(lvlName, player, window);
}

int Engine::startMainMenu() {
	window.setMouseCursorVisible(true);
	return mainMenu.invokeMenu(window);
}

void Engine::closeSession() {
	view.reset(FloatRect(0, 0, resolution.x, resolution.y));
	window.setView(view);
	lvl.clear();
	player.inventory.clear();
	if (inventoryIsOpen) inventoryIsOpen = false;
	sleep(milliseconds(150));
}

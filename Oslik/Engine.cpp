#include "Engine.h"

Engine::Engine() {
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	window.create(VideoMode(resolution.x, resolution.y), "Game Engine v0.2", Style::Fullscreen);
	view.reset(FloatRect(0, 0, resolution.x, resolution.y));
	// Вынести в отдельный метод инициализации анимации через цикл у всех существ;
	menu.initializeMenu(Vector2f(250, 500), Vector2f(250, 100));
	mainMenu.initializeMenu(Vector2f(250, 500), Vector2f(250, 100));
}

void Engine::initialization() {
	
	offsetX = resolution.x / 2;
	offsetY = resolution.y / 2;
	lvl.loadLVL(std::string("maps/lvl.txt"));
	player.initialize("testhero.png", lvl.map, lvl.blockSize, lvl.spawnPoint);

	update(0);
	draw();
	sleep(milliseconds(100));
}


void Engine::input(Event event, float time) {
	
	if (event.type == Event::KeyPressed) {

		if (event.key.code == (Keyboard::Escape)) {
			menuIsOpen = true;
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
			// Наверно через это будет реализован инвентарь -_- (Максим привет!)
		}

	}

	else if (event.type == Event::KeyReleased) {

		if ((!Keyboard::isKeyPressed(Keyboard::D)) && !(Keyboard::isKeyPressed(Keyboard::A))) {
			player.stopX();
		}

		if (event.key.code == (Keyboard::LShift) && !Keyboard::isKeyPressed(Keyboard::LShift)) {
			player.stopRun();
		}		

		if (event.key.code == (Keyboard::A) && Keyboard::isKeyPressed(Keyboard::D)) player.moveRight(time);

		if (event.key.code == (Keyboard::D) && Keyboard::isKeyPressed(Keyboard::A)) player.moveLeft(time);
		
	}
}

void Engine::draw() {
	window.clear(Color::White);
	window.setView(view);
	lvl.draw(window, view);
	player.animation.draw(window, player.hitBox.left, player.hitBox.top);
	window.display();
}

void Engine::update(float time) {
	//worldUpdate(time);
	player.update(time);
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
	if (menuIsOpen) {
		menuIsOpen = false;
		if (menu.invokeMenu(window)) return 0;
		clock.restart();
	}
	return 1;
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
	return mainMenu.invokeMenu(window);
}

void Engine::closeSession() {
	view.reset(FloatRect(0, 0, resolution.x, resolution.y));
	window.setView(view);
}

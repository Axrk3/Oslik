#include "Engine.h"


Engine::Engine() {
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	window.create(VideoMode(resolution.x, resolution.y), "Game Engine v.1.1", Style::Fullscreen);
	view.reset(FloatRect(0, 0, resolution.x, resolution.y));

	//backgroundTexture.loadFromFile("back.jpg");
	//backgroundSprite.setTexture(backgroundTexture);
	lvl.loadLVL(std::string("maps/lvl.txt"));
	player.initialize("testsprite.png",lvl);
	player.animation.create("walk", player.texture,0,0,150,63,9,5,150);
	player.animation.set("walk");
	player.animation.play();
}


void Engine::input(Event event, float time) {
	
	if (event.type == Event::KeyPressed) {

		if (event.key.code == (Keyboard::Escape)) {
			window.close();
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


	}

	else if (event.type == Event::KeyReleased) {

		if ((!Keyboard::isKeyPressed(Keyboard::D)) && !(Keyboard::isKeyPressed(Keyboard::A))) {
			player.stopX();
		}

		if (!Keyboard::isKeyPressed(Keyboard::LShift)) {
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
	window.draw(player.sprite);
	// ������ ������� �������� ������� ����� ���������� ��������
	//player.animation.draw(window, 200, 400);
	window.display();
}

void Engine::update(float time) {
	//worldUpdate(time);
	player.update(time);
	view.setCenter(player.rect.left, player.rect.top);
}

void Engine::start() {
	Clock clock;
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		Event event;
		while (window.pollEvent(event))
		{
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
		update(time);
		draw();
	}
}


/*Engine::Engine() {
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	window.create(VideoMode(resolution.x, resolution.y), "Game Engine v.1", Style::Fullscreen);

	backgroundTexture.loadFromFile("back.jpg");
	backgroundSprite.setTexture(backgroundTexture);

	regularFont.loadFromFile("times.ttf");
	regularText.setFont(regularFont);

	offsetX = offsetY = 0;

	blockSize = 64;
	rectSize.x = blockSize; rectSize.y = blockSize;
	rect.setSize(rectSize);
	lvl.changeLevel(map1);

}

void Engine::input() {
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	if (Keyboard::isKeyPressed(Keyboard::I)) {
		if (openInventory) openInventory = false;
		else {
			player.dx = 0; player.dy = 0;
			openInventory = true;
			openChest = false;
		}
	}
	// ���� ��������� ������ ���������� ���������
	if (!openInventory) {

		if (Keyboard::isKeyPressed(Keyboard::A)) {
			player.dx = -300;
		}
		else {
			player.dx = 0;
		}

		if (Keyboard::isKeyPressed(Keyboard::D)) {
			player.dx = 300;
		}

		if (Keyboard::isKeyPressed(Keyboard::LShift)) player.dx *= 3;

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			player.Jump();
		}
	}
}

void Engine::update(float time) {
	player.rect.left += player.dx * time;

	collision(0);

	player.dy += 1000 * time;

	player.rect.top += player.dy * time;

	collision(1);

	player.sprite.setPosition(player.rect.left - offsetX, player.rect.top - offsetY);
}

// 0 - x; 1 - y
void Engine::collision(int dir) {
	for (int i = player.getRect().top / blockSize; i < (player.getRect().top + player.getRect().height) / blockSize; i++) {
		for (int j = player.getRect().left / blockSize; j < (player.getRect().left + player.getRect().width) / blockSize; j++) {
			if ((lvl.getMap()[i][j] == 'D') || (lvl.getMap()[i][j] == 'G')) {
				if ((player.dx > 0) && (dir == 0)) player.setRect(0, j * blockSize - player.getRect().width);
				if ((player.dx < 0) && (dir == 0)) player.setRect(0, j * blockSize + blockSize);
				if ((player.dy > 0) && (dir == 1)) {
					player.setRect(1, i * blockSize - player.getRect().height);
					player.dy = 0; 
				}
				if ((player.dy < 0) && (dir == 1)) {
					player.setRect(1, i * blockSize + blockSize);
					player.dy = 0;
				}
			} 
			
			if ((lvl.getMap()[i][j] == 'C' || lvl.getMap()[i][j] == 'T') && (Keyboard::isKeyPressed(Keyboard::E))) {
				if (lvl.getMap()[i][j] == 'C') {
					lvl.changeBlock(i, j);
					lvl.changeBlock(i, j + 1);
					
				} else {
					lvl.changeBlock(i, j);
					lvl.changeBlock(i, j - 1);
				}
				player.inventory.addItem(player.inventory.consum[0], "test item");
				regularText.setString("You got item!!");
				regularText.setCharacterSize(32);
				regularText.setFillColor(Color::Yellow);
				regularText.setPosition(i, j);
				openChest = true;
			}
		}
	}
}

void Engine::drawMap(String map[]) {

	for (int i = 0; i < 34; i++) {
		for (int j = 0; j < 80; j++) {
			switch (map[i][j]) {
			case 'D': rect.setTexture(&lvl.dirt);
					  break;
			case 'G': rect.setTexture(&lvl.grass);
					  break;
			case 'C': rect.setTexture(&lvl.chestLeft);
					  break;
			case 'T': rect.setTexture(&lvl.chestRight);
					  break;
			default: continue;
			}
			rect.setPosition(j * blockSize - offsetX,i * blockSize - offsetY);
			window.draw(rect);
		}
	}
}

void Engine::drawInventory() {
	player.inventory.rect.setPosition(resolution.x/4, resolution.y/4);
	window.draw(player.inventory.rect);
	if (player.inventory.consum[0].maxQuantity > 0) {
		regularText.setString(player.inventory.consum[0].name);
		regularText.setCharacterSize(14);
		regularText.setFillColor(Color::Black);
		regularText.setPosition(resolution.x / 4 + 128, resolution.y / 4 + 64);
		window.draw(regularText);
	}
}

void Engine::draw() {
	window.clear(Color::White);
	window.draw(backgroundSprite);
	drawMap(lvl.getMap());
	window.draw(player.getSprite());
	if (openInventory) drawInventory();
	if (openChest) window.draw(regularText);
	window.display();
}

void Engine::start() {
	Clock clock;
	while (window.isOpen()) {
		Time dt = clock.restart();
		float time = dt.asSeconds();
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case Event::Closed:
				window.close();
				break;

			case Event::KeyPressed : {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
				input();
				break;
			}
			case Event::KeyReleased: {
				input();
				break;
			}
			default:
				break;
			}
		}
		update(time);
		if (player.rect.left > resolution.x / 2 && player.rect.left < 80 * blockSize - resolution.x / 2) offsetX = player.rect.left - resolution.x / 2;
		if (player.rect.top > resolution.y / 2 && player.rect.top < 34 * blockSize - resolution.y / 2) offsetY = player.rect.top - resolution.y / 2;
		draw();
	}
}*/
#include "Battle.h"

Battle::Battle(Player &_player, RenderWindow &_window) {
	player = _player;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	battleView.reset(FloatRect(0, 0, resolution.x, resolution.y));

	window = &_window;
}

void Battle::battleInitialization(Enemy *enemy) {
	menuInitialization();
	cursorInitialization();
	playerInitialization();
	enemyInitialization(enemy);
}

void Battle::battleStart(Enemy *enemy) {
	battleInitialization(enemy);

	while (player.getStats().HP >= 0 && !enemies.empty()) {
		draw();

		cursorSprite.setPosition(currentPosition);
		input();
		actionProcessing();
		cursorSprite.setPosition(currentPosition);

		if (isAction) {
			for (int i = 0; i < enemies.size(); i++) {
				attack(*enemies.at(i), player, -20, (i == 1) ? 0 : i ? -1 : 1);
			}

			if (isBlocked) {
				defenceDown(player);
				isBlocked = false;
			}

			isAction = false;
		}

		window->display();
	}
}

void Battle::menuInitialization() {
	menuTexture.loadFromFile("menu.png");
	menuSprite.setTexture(menuTexture);
	menuSprite.setPosition(384, 810);

	barSize.x = 219;
	barSize.y = 91;

	barHitBox = new RectangleShape[4];
	for (int i = 0; i < 4; i++) {
		barHitBox[i].setFillColor(Color::Transparent);
		barHitBox[i].setSize(barSize);
	}
	barHitBox[0].setPosition(menuSprite.getPosition().x + 62, menuSprite.getPosition().y + 37);
	barHitBox[1].setPosition(menuSprite.getPosition().x + 380, menuSprite.getPosition().y + 37);
	barHitBox[2].setPosition(menuSprite.getPosition().x + 62, menuSprite.getPosition().y + 139);
	barHitBox[3].setPosition(menuSprite.getPosition().x + 380, menuSprite.getPosition().y + 139);

	hpBarInitialization();
}

void Battle::hpBarInitialization() {
	hpBarSize.x = 199;
	hpBarSize.y = 44;

	hpModifier = hpBarSize.x / player.stats.HP;

	hpBar.setPosition(menuSprite.getPosition().x + 698, menuSprite.getPosition().y + 61);
	hpBar.setSize(hpBarSize);
	hpBar.setFillColor(Color(220, 20, 60, 255));
}

void Battle::cursorInitialization() {
	cursorTexture.loadFromFile("cursor.png");
	cursorSprite.setTexture(cursorTexture);

	action.x = 0;
	action.y = 0;
	currentPosition = barHitBox[(action.x + action.y)].getPosition();
}

void Battle::playerInitialization() {
	player.getSprite().setPosition(384, 540);
}

void Battle::enemyInitialization(Enemy *enemy) {
	enemies.push_back(enemy);

	if (randomGenerator(40)) {
		enemies.push_back(EnemyFactory::createEnemy(0, 0, enemy->getID()));

		if (randomGenerator(30)) {
			enemies.push_back(EnemyFactory::createEnemy(0, 0, enemy->getID()));
		}
	}

	enemyCoordinatesSet();
}

void Battle::enemyCoordinatesSet() {
	if (enemies.size() == 1) {
		enemies.front()->sprite.setPosition(1536, 540);
	}
	else if (enemies.size() == 2) {
		enemies.front()->sprite.setPosition(1416, 270);
		enemies.back()->sprite.setPosition(1656, 810);
	}
	else {
		enemies.at(0)->sprite.setPosition(1416, 270);
		enemies.at(1)->sprite.setPosition(1536, 540);
		enemies.at(2)->sprite.setPosition(1656, 810);
	}
}

void Battle::input() {
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		if (action.y == 1) {
			action.y--;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		if (action.y == 0) {
			action.y++;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		if (action.x == 1) {
			action.x--;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		if (action.x == 0) {
			action.x++;
		}
	}

	currentPosition.x = barHitBox[(action.x + 2 * action.y)].getPosition().x + barSize.x;
	currentPosition.y = barHitBox[(action.x + 2 * action.y)].getPosition().y;
}

void Battle::attack(Character& attacker, Character& defender, int speedX, int speedY) {
	Vector2f offset;
	offset.x = speedX * 0.05;
	offset.y = speedY * 0.1;
	int step = 0;

	while (attacker.sprite.getPosition().x != defender.sprite.getPosition().x) {
		attacker.sprite.move(offset);
		step++;

		draw();
		window->display();
	}



	if (attacker.stats.ATK > defender.stats.DEF)
		defender.stats.HP -= (attacker.stats.ATK - defender.stats.DEF);

	if (defender.getStats().HP <= 0) {
		defender.stats.HP = 0;
	}

	while (step) {
		attacker.sprite.move(-offset);
		step--;

		draw();
		window->display();
	}
}

int Battle::chooseEnemy() {
	int choice = 0;

	do {
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			if (choice != 0) {
				choice--;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			if (choice != 2) {
				choice++;
			}
		}

		cursorSprite.setPosition(enemies.at(choice)->sprite.getPosition().x + enemies.at(choice)->texture.getSize().x, enemies.at(choice)->sprite.getPosition().y);

		draw();
		window->display();
		sleep(seconds(0.1f));
	} while (!Keyboard::isKeyPressed(Keyboard::Enter));

	return choice;
}

void Battle::actionProcessing() {
	int choice;

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		switch (action.x + 2 * action.y) {
		case 0:
			choice = chooseEnemy();
			attack(player, *enemies.at(choice), 20, (choice == 1) ? 0 : choice ? 1 : -1);
			break;
		case 1:
			defenceUp(player);
			isBlocked = true;
			break;
		case 2:

			break;
		case 3:
			exit(0);
			break;
		}

		isAction = true;
	}
}

void Battle::defenceUp(Character& defender) {
	defender.stats.DEF *= 2;
}

void Battle::defenceDown(Character& defender) {
	defender.stats.DEF /= 2;
}

void Battle::draw() {
	window->clear(Color::White);

	window->draw(player.getSprite());
	for (int i = 0; i < enemies.size(); i++) {
		window->draw(enemies.at(i)->getSprite());
	}

	hpBarSize.x = player.stats.HP * hpModifier;
	hpBar.setSize(hpBarSize);

	window->draw(menuSprite);
	window->draw(cursorSprite);
	window->draw(hpBar);
}

bool Battle::randomGenerator(int probability) {
	srand(time(NULL));

	if (rand() % 101 <= probability)
		return 1;
	else
		return 0;
}
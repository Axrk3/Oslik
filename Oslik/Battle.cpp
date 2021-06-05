#include "Battle.h"

Battle::Battle() {
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	battleView.reset(FloatRect(0, 0, resolution.x, resolution.y));
}

void Battle::create(Player &_player, RenderWindow &_window) {
	player = &_player;
	window = &_window;
}

bool Battle::start(Enemy &enemy) {

	objectsInitialization(enemy);

	while (player->getStats().HP > 0 && !enemies.empty() && !exitFlag) {
		draw();

		cursorSprite.setPosition(currentPosition);
		input();
		actionProcessing();
		cursorSprite.setPosition(currentPosition);

		if (isAction) {
			for (int i = 0; i < enemies.size(); i++) {
				if (player->getStats().HP) {
					attack(*enemies.at(i), *player);
				}
			}

			if (isBlocked) {
				defenceDown(*player);
				isBlocked = false;
			}

			isAction = false;
		}
		window->display();
	}
	if (!player->getStats().HP) {
		isDead = true;
	}
	endScreen();
	enemies.clear();
	return isDead;
}

void Battle::endScreen() {
	if (isDead) {
		endBattleTexture.loadFromFile("dead.png");
		window->clear(Color::Black);
	}
	else {
		endBattleTexture.loadFromFile("win.png");
		window->clear(Color::White);
	}
	endBattleSprite.setTexture(endBattleTexture);
	endBattleSprite.setPosition((resolution.x - endBattleTexture.getSize().x) / 2, (resolution.y - endBattleTexture.getSize().y) / 2);
	window->draw(endBattleSprite);
	window->display();
	while (!Keyboard::isKeyPressed(Keyboard::Escape));
}

void Battle::objectsInitialization(Enemy &enemy) {
	window->setView(battleView);
	menuInitialization();
	cursorInitialization();
	playerInitialization();
	enemyInitialization(enemy);
	exitFlag = false;
	isDead = false;
}

void Battle::menuInitialization() {
	menuTexture.loadFromFile("battleMenu.png");
	menuSprite.setTexture(menuTexture);
	menuSprite.setPosition(0, resolution.y - 260);

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

	hpModifier = hpBarSize.x / player->stats.HP;

	hpBar.setPosition(menuSprite.getPosition().x + 694, menuSprite.getPosition().y + 57);
	hpBar.setSize(hpBarSize);
	hpBar.setFillColor(Color(220, 20, 60, 255));
}

void Battle::cursorInitialization() {
	cursorTexture.loadFromFile("battleCursor.png");
	cursorSprite.setTexture(cursorTexture);

	action.x = 0;
	action.y = 0;
	currentPosition = barHitBox[(action.x + action.y)].getPosition();
}

void Battle::playerInitialization() {
	player->sprite.setPosition(resolution.x / 5, 3 * resolution.y / 8);
}

void Battle::enemyInitialization(Enemy &enemy) {
	enemies.push_back(&enemy);

	if (randomGenerator(40)) {
		enemies.push_back(EnemyFactory::createEnemy(0, 0, enemy.getID()));

		if (randomGenerator(20)) {
			enemies.push_back(EnemyFactory::createEnemy(0, 0, enemy.getID()));
		}
	}

	enemyCoordinatesSet();
}

void Battle::enemyCoordinatesSet() {
	if (enemies.size() == 1) {
		enemies.front()->sprite.setPosition(1536, 3 * resolution.y / 8);
	}
	else if (enemies.size() == 2) {
		enemies.front()->sprite.setPosition(1416, resolution.y / 8);
		enemies.back()->sprite.setPosition(1656, 5 * resolution.y / 8);
	}
	else {
		enemies.at(0)->sprite.setPosition(1416, resolution.y / 8);
		enemies.at(1)->sprite.setPosition(1536, 3 * resolution.y / 8);
		enemies.at(2)->sprite.setPosition(1656, 5 * resolution.y / 8);
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

void Battle::attack(Player& attacker, Enemy& defender) {
	Vector2f offset;
	offset.x = (defender.sprite.getPosition().x - attacker.sprite.getPosition().x) / 30;
	offset.y = (defender.sprite.getPosition().y - attacker.sprite.getPosition().y) / 30;
	int step = 0;

	while (attacker.sprite.getPosition().x <= defender.sprite.getPosition().x) {
		attacker.sprite.move(offset);
		step++;

		draw();
		window->display();
	}



	if (attacker.stats.ATK > defender.stats.DEF)
		defender.stats.HP -= (attacker.stats.ATK - defender.stats.DEF);

	if (defender.getStats().HP <= 0) {
		for (int i = 0; i < enemies.size(); i++) {
			if (enemies.at(i) == &defender) {
				enemies.erase(enemies.begin() + i);
			}
		}
	}

	while (step) {
		attacker.sprite.move(-offset);
		step--;

		draw();
		window->display();
	}
}

void Battle::attack(Enemy& attacker, Player& defender) {
	Vector2f offset;
	offset.x = (defender.sprite.getPosition().x - attacker.sprite.getPosition().x) / 30;
	offset.y = (defender.sprite.getPosition().y - attacker.sprite.getPosition().y) / 30;
	int step = 0;

	while (attacker.sprite.getPosition().x >= defender.sprite.getPosition().x) {
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
			if (choice != enemies.size() - 1) {
				choice++;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			choice = -1;
			break;
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
			if (choice > -1) {
				attack(*player, *enemies.at(choice));
				isAction = true;
			}
			break;
		case 1:
			defenceUp(*player);
			isAction = true;
			isBlocked = true;
			break;
		case 2:
			window->setMouseCursorVisible(true);
			while (!Keyboard::isKeyPressed(Keyboard::Escape)) {
				player->openInventory(*window, battleView.getCenter());
			}
			window->setMouseCursorVisible(false);
			isAction = true;
			break;
		case 3:
			exitFlag = true;
			break;
		}
	}
}

void Battle::defenceUp(Character &defender) {
	defender.stats.DEF *= 2;
}

void Battle::defenceDown(Character& defender) {
	defender.stats.DEF /= 2;
}

void Battle::draw() {
	window->clear(Color::White);

	window->draw(player->getSprite());
	for (int i = 0; i < enemies.size(); i++) {
		window->draw(enemies.at(i)->getSprite());
	}

	hpBarSize.x = player->stats.HP * hpModifier;
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
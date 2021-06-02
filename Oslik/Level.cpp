#include "Level.h"

Level::Level() {
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
}

void Level::loadLVL(const string _fileName, Player &_player, RenderWindow &window) {
    string line,path = "maps/";
    int x, y, num;
    fileName = _fileName;

    battle.create(_player, window);

    ifstream in(_fileName);
    if (in.is_open()) {
        getline(in, line);
        in >> mapSize.x; in >> mapSize.y;
        map = new int* [mapSize.y];
        for (int i = 0; i < mapSize.y; i++) {
            map[i] = new int[mapSize.x];
        }

        getline(in, line);
        getline(in, line);
        blockSize = atoi(line.substr(10).c_str());
        tile.setSize(Vector2f(blockSize, blockSize));

        // Закинуть текстуры в папку maps и приклеить к началу строки maps/
        getline(in, line);
        tileSet.loadFromFile(path + line.substr(line.find('"') + 1));
        tile.setTexture(&tileSet);
        
        getline(in, line);
        tileSetWidth = atoi(line.substr(15).c_str());

        getline(in,line);
        backgroundTexture.loadFromFile(path + line.substr(line.find('"') + 1));
        backgroundSprite.setTexture(backgroundTexture);
        
        // block array
        for (int i = 0; i < mapSize.y; i++) {
            for (int j = 0; j < mapSize.x; j++) {
                in >> map[i][j];
            }
        }

        while (!in.eof()) {
            getline(in, line);
            if (!line.compare("SPAWN_POINT")) readSpawnPoint(in);
            if (!line.compare("FRIEND")) readFriend(in);
            if (!line.compare("ENEMY")) readEnemy(in);
            if (!line.compare("ITEM")) readItem(in);
            if (!line.compare("END")) readEndPoint(in);
        }
    }
    in.close();
}

void Level::calculateTile(int tileID) {
    if (tileID % tileSetWidth == 0) tileIDcord.x = (tileSetWidth - 1) * blockSize;
    else tileIDcord.x = (tileID % tileSetWidth - 1) * blockSize;

    if (tileID / tileSetWidth == 0) tileIDcord.y = 0;
    else if (tileID % tileSetWidth == 0) tileIDcord.y = ((tileID / tileSetWidth) - 1) * blockSize;
    else tileIDcord.y = (tileID / tileSetWidth) * blockSize;

    tile.setTextureRect(IntRect(tileIDcord.x, tileIDcord.y, blockSize, blockSize));
}

void Level::readSpawnPoint(ifstream &in) {
    in >> spawnPoint.x; in >> spawnPoint.y;
}

void Level::readFriend(ifstream &in) {
    int x, y, id;

    while (true) {
        in >> x;
        if (x == -1) break;
        in >> y; in >> id;
        //friends.push_back(*FriendFactory::createFriend(x, y, id));
    }
}

void Level::readEnemy(ifstream &in) {
    int x, y, id;

    while (true) {
        in >> x;
        if (x == -1) break;
        in >> y; in >> id;
        enemies.push_back(*EnemyFactory::createEnemy(x, y, id));
    }
}

void Level::readItem(ifstream &in) {
    int x, y, id;

    while (true) {
        in >> x;
        if (x == -1) break;
        in >> y; in >> id;
        items.push_back(*ItemFactory::createItem(x, y, id));
    }
}

void Level::readEndPoint(ifstream &in) {
    in >> endPoint.left; in >> endPoint.top;
    //in >> endPoint.width; in >> endPoint.height;
}

void Level::drawMap(RenderWindow &window) {
    // resolution.x / 2 = 960, resolution.y / 2 = 540, blockSize = 64;
    for (int i = (viewCord.y - 540) / 64 - 1 < 0 ? 0 : (viewCord.y - 540) / 64 - 1;
        i < ((viewCord.y + 540) / 64  + 1 > mapSize.y ? mapSize.y : (viewCord.y + 540) / 64 + 1); i++) {
        for (int j = (viewCord.x - 960) / 64 - 1 < 0 ? 0 : (viewCord.x - 960) / 64 - 1;
            j < ((viewCord.x + 960) / 64 + 1 > mapSize.x ? mapSize.x : (viewCord.x + 960) / 64 + 1); j++) {
            if (map[i][j] == 0) continue;
            calculateTile(map[i][j]);
            tile.setPosition(j * blockSize, i * blockSize);
            window.draw(tile);
        }
    }
}

void Level::drawBackground(RenderWindow &window) {
    backgroundSprite.setPosition(viewCord.x - resolution.x / 2, viewCord.y - resolution.y / 2);
    window.draw(backgroundSprite);
}

void Level::drawEnemies(RenderWindow &window) {
    Vector2f enemyCord;
    int enemyWidth, enemyHeight;
    for (int i = 0; i < enemies.size(); i++) {
        enemyCord.x = enemies.at(i).getHitBox().left; enemyCord.y = enemies.at(i).getHitBox().top;
        enemyWidth = enemies.at(i).getHitBox().width; enemyHeight = enemies.at(i).getHitBox().height;
        if (enemyCord.x > viewCord.x - 960 - enemyWidth &&
            enemyCord.x < (viewCord.x + 960)) {
            if (enemyCord.y > viewCord.y - 540 - enemyHeight &&
                enemyCord.y < (viewCord.y + 540)) {
                window.draw(enemies.at(i).getSprite());
            }
        }
    }
}

void Level::drawFriends(RenderWindow &window) {
    Vector2f friendCord;
    int friendWidth, friendHeight;
    for (int i = 0; i < friends.size(); i++) {
        friendCord.x = friends.at(i).getHitBox().left; friendCord.y = friends.at(i).getHitBox().top;
        friendWidth = friends.at(i).getHitBox().width; friendHeight = friends.at(i).getHitBox().height;
        if (friendCord.x > viewCord.x - 960 - friendWidth &&
            friendCord.x < (viewCord.x + 960)) {
            if (friendCord.y > viewCord.y - 540 - friendHeight &&
                friendCord.y < (viewCord.y + 540)) {
                window.draw(friends.at(i).getSprite());
            }
        }
    }
}

void Level::drawItems(RenderWindow &window) {
    Vector2f itemCord;
    int itemWidth, itemHeight;
    for (int i = 0; i < items.size(); i++) {
        itemCord.x = items.at(i).getHitBox().left; itemCord.y = items.at(i).getHitBox().top;
        itemWidth = items.at(i).getHitBox().width; itemHeight = items.at(i).getHitBox().height;
        if (itemCord.x > viewCord.x - 960 - itemWidth &&
            itemCord.x < (viewCord.x + 960)) {
            if (itemCord.y > viewCord.y - 540 - itemHeight &&
                itemCord.y < (viewCord.y + 540)) {
                window.draw(items.at(i).getSprite());
            }
        }
    }
}

void Level::draw(RenderWindow &window) {
    drawBackground(window);
    drawEnemies(window);
    //drawFriends(window);
    drawItems(window);
    drawMap(window);
}

void Level::worldUpdate(Player &player, Clock &clock, Vector2f viewCenter) {
    viewCord = viewCenter;

    for (int i = 0; i < enemies.size(); i++) {
        if (enemies.at(i).getHitBox().left > viewCord.x - 960 && enemies.at(i).getHitBox().left < viewCord.x + 960 &&
            enemies.at(i).getHitBox().top > viewCord.y - 540 && enemies.at(i).getHitBox().top < viewCord.y + 540) {
            if (enemies.at(i).playerIntersection(player)) {
                battle.start(enemies.at(i));
                enemies.erase(enemies.begin() + i);
                clock.restart();
            }
        }
    }

    for (int i = 0; i < items.size(); i++) {
        if (items.at(i).getHitBox().left > viewCord.x - 960 && items.at(i).getHitBox().left < viewCord.x + 960 &&
            items.at(i).getHitBox().top > viewCord.y - 540 && items.at(i).getHitBox().top < viewCord.y + 540) {
            if (items.at(i).playerIntersection(player)) {
                player.inventory.addItem(items.at(i));
                items.erase(items.begin() + i);
            }
        }
    }

    if (endPoint.intersects(player.hitBox)) {
        return;
    }
}

void Level::clear() {
    friends.clear();
    items.clear();
    enemies.clear();
    delete (map);
}

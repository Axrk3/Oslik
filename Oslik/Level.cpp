#include "Level.h"

using namespace std;

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
        // spawnpoint
        in >> line;
        in >> spawnPoint.x; in >> spawnPoint.y;
        // Friends
        in >> line;
        while (true) {
            in >> x;
            if (x == -1) break;
            in >> y; in >> num;
            //friends.push_back(*EnemyFactory::createFriend(x, y, num));
        }
        // Enemies
        in >> line;
        while (true) {
            in >> x;
            if (x == -1) break;
            in >> y; in >> num;
            enemies.push_back(*EnemyFactory::createEnemy(x, y, num));
        }
        // Items
        in >> line;
        while (true) {
            in >> x;
            if (x == -1) break;
            in >> y; in >> num;
            items.push_back(*ItemFactory::createItem(x, y, num));
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

void Level::drawMap(RenderWindow &window, View view) {
    // resolution.x/2 = 960, resolution.y/2 = 540, blockSize = 64;
    Vector2f viewCord;
    viewCord.x = view.getCenter().x;
    viewCord.y = view.getCenter().y;
    for (int i = (viewCord.y - 540) / 64 < 0 ? 0 : (viewCord.y - 540) / 64;
        i < ((viewCord.y + 540) / 64 > mapSize.y ? mapSize.y : (viewCord.y + 540) / 64); i++) {
        for (int j = (viewCord.x - 960) / 64 < 0 ? 0 : (viewCord.x - 960) / 64;
            j < ((viewCord.x + 960) / 64 > mapSize.x ? mapSize.x : (viewCord.x + 960) / 64); j++) {
            if (map[i][j] == 0) continue;
            calculateTile(map[i][j]);
            tile.setPosition(j * blockSize, i * blockSize);
            window.draw(tile);
        }
    }
}

void Level::drawBackground(RenderWindow &window, View view) {
    backgroundSprite.setPosition(view.getCenter().x - resolution.x / 2,view.getCenter().y - resolution.y / 2);
    window.draw(backgroundSprite);
}

void Level::drawEnemies(RenderWindow& window, View view) {
    Vector2f enemyCord, viewCord;
    int enemyWidth, enemyHeight;
    viewCord.x = view.getCenter().x;
    viewCord.y = view.getCenter().y;
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

void Level::drawFriends(RenderWindow& window, View view) {
    Vector2f friendCord, viewCord;
    int friendWidth, friendHeight;
    viewCord.x = view.getCenter().x;
    viewCord.y = view.getCenter().y;
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

void Level::drawItems(RenderWindow& window, View view) {
    Vector2f itemCord, viewCord;
    int itemWidth, itemHeight;
    viewCord.x = view.getCenter().x;
    viewCord.y = view.getCenter().y;
    for (int i = 0; i < enemies.size(); i++) {
        itemCord.x = enemies.at(i).getHitBox().left; itemCord.y = enemies.at(i).getHitBox().top;
        itemWidth = enemies.at(i).getHitBox().width; itemHeight = enemies.at(i).getHitBox().height;
        if (itemCord.x > viewCord.x - 960 - itemWidth &&
            itemCord.x < (viewCord.x + 960)) {
            if (itemCord.y > viewCord.y - 540 - itemHeight &&
                itemCord.y < (viewCord.y + 540)) {
                window.draw(enemies.at(i).getSprite());
            }
        }
    }
}

void Level::draw(RenderWindow& window, View view) {
    drawBackground(window, view);
    drawEnemies(window, view);
    //drawFriends(window, view);
    //drawItems(window,view);
    drawMap(window,view);
}

void Level::worldUpdate(Player &player, Clock &clock) {
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies.at(i).playerIntersection(player)) {
            battle.start(enemies.at(i));
            enemies.erase(enemies.begin() + i);
            clock.restart();
        }
    }
}

void Level::clear() {
    friends.clear();
    items.clear();
    enemies.clear();
    delete (map);
}

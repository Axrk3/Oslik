#include "Level.h"
using namespace std;

Level::Level() {
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
}

void Level::loadLVL(const string _fileName) {
    string line;
    fileName = _fileName;

    ifstream in(_fileName);
    if (in.is_open())
    {
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
        tileSet.loadFromFile(line.substr(line.find('"') + 1));
        tile.setTexture(&tileSet);
        
        getline(in, line);
        tileSetWidth = atoi(line.substr(15).c_str());

        getline(in,line);
        backgroundTexture.loadFromFile(line.substr(line.find('"') + 1));
        backgroundSprite.setTexture(backgroundTexture);
        
        /*getline(in, line); getline(in, line);
        spawnPoint.x = atoi(line.c_str());
        getline(in, line);
        spawnPoint.y = atoi(line.c_str());*/
        spawnPoint.x = 200; spawnPoint.y = 400;

        for (int i = 0; i < mapSize.y; i++) {
            for (int j = 0; j < mapSize.x; j++) {
                in >> map[i][j];
            }
        }
    }
    in.close();
}

void Level::calculateTile(int tileID) {
    if (tileID % tileSetWidth == 0) tileIDcord.x = tileSetWidth - 1 * blockSize;
    else tileIDcord.x = (tileID % tileSetWidth - 1) * blockSize;

    if (tileID / tileSetWidth == 0) tileIDcord.y = tileSetWidth - 1 * blockSize;
    else tileIDcord.y = (tileID / tileSetWidth) * blockSize;

    tile.setTextureRect(IntRect(tileIDcord.x, tileIDcord.y, blockSize, blockSize));
}

void Level::drawMap(RenderWindow &window) {
    for (int i = 0; i < mapSize.y; i++) {
        for (int j = 0; j < mapSize.x; j++) {
            if (map[i][j] == 0) continue;
            calculateTile(map[i][j]);
            tile.setPosition(j * blockSize, i * blockSize);
            window.draw(tile);
        }
    }
}

void Level::drawBackground(RenderWindow& window,View view) {
    backgroundSprite.setPosition(view.getCenter().x - resolution.x / 2,view.getCenter().y - resolution.y / 2);
    window.draw(backgroundSprite);
}

void Level::draw(RenderWindow& window, View view) {
    drawBackground(window, view);
    drawMap(window);
}

void Level::worldUpdate() {

}

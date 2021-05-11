#include "Level.h"

using namespace std;

Level::Level() {
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
}

void Level::loadLVL(const string _fileName) {
    string line;
    int x, y, num;
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
        
        // block array
        for (int i = 0; i < mapSize.y; i++) {
            for (int j = 0; j < mapSize.x; j++) {
                in >> map[i][j];
            }
        }
        // spawnpoint
        in >> line;
        in >> spawnPoint.x; in >> spawnPoint.y;
        // friend
        in >> line;
        in >> x; in >> y; in >> num;
        // createFriend(x,y,num);
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
    for (int i = (view.getCenter().y - 540) / 64 < 0 ? 0 : (view.getCenter().y - 540) / 64;
        i < ((view.getCenter().y + 540) / 64 > mapSize.y ? mapSize.y : (view.getCenter().y + 540) / 64); i++) {
        for (int j = (view.getCenter().x - 960) / 64 < 0 ? 0 : (view.getCenter().x - 960) / 64;
            j < ((view.getCenter().x + 960) / 64 > mapSize.x ? mapSize.x : (view.getCenter().x + 960) / 64); j++) {
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
    drawMap(window,view);
}

void Level::worldUpdate() {

}

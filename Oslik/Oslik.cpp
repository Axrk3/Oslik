#include <SFML/Graphics.hpp>
#include "Engine.h"

int main() {
    Engine engine;
    do {
        switch (engine.startMainMenu()) {
        case 1:
            engine.start("maps/lvl1.txt");
            break;
        case 2:
            engine.start("maps/saveFile.txt");
            break;
        }
    } while (true);
    
    return 0;
}

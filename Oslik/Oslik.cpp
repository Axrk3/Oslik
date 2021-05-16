#include <SFML/Graphics.hpp>
#include "Engine.h"

int main() {
    Engine engine;
    // Костылина та ещё, сделать главное меню другим классом 
    //engine.startMainMenu();
    do {
        switch (engine.startMainMenu()) {
        case 0: engine.start();
        }
    } while (true);
    return 0;
}

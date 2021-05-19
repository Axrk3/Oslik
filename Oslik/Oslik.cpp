#include <SFML/Graphics.hpp>
#include "Engine.h"

int main() {
    Engine engine;
    do {
        switch (engine.startMainMenu()) {
        case 1: {
            engine.start();
        }
        // Настройки
        // Сохранения
        }
    } while (true);
    
    return 0;
}

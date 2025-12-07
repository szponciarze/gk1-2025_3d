#include <iostream>
#include "Engine.h"
#include <SDL.h>

int main(int argc, char* args[]) {
    Engine engine;

    if (engine.init("Okno 3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false, true, true, 144, true)) {
        engine.mainLoop();
    }
    else {
        std::cerr << "Blad inicjalizacji silnika 3D!" << std::endl;
    }

    return 0;
}
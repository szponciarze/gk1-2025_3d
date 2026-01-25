/**
 * @file main.cpp
 * @brief Punkt wejœcia do aplikacji wykorzystuj¹cej silnik 3D.
 *
 * Plik zawiera funkcjê main, która inicjalizuje
 * silnik 3D oraz uruchamia jego g³ówn¹ pêtlê.
 */

#include <iostream>
#include "Engine.h"
#include <SDL.h>


 /**
  * @brief G³ówna funkcja programu.
  *
  * Tworzy instancjê silnika 3D, inicjalizuje go
  * oraz uruchamia g³ówn¹ pêtlê renderuj¹c¹.
  *
  * @param argc Liczba argumentów wiersza poleceñ
  * @param args Tablica argumentów wiersza poleceñ
  * @return Kod zakoñczenia programu
  */
int main(int argc, char* args[]) {
    Engine engine;

    if (engine.init("Okno 3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false, true, true, 144, true,3)) {
        engine.mainLoop();
    }
    else {
        std::cerr << "Blad inicjalizacji silnika 3D!" << std::endl;
    }

    return 0;
}
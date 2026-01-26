/**
 * @file Cube.h
 * @brief Klasa reprezentuj¹ca szeœcian.
 */

#pragma once
#include "Primitive.h"
#include <vector>
#include <SDL_opengl.h>
#include <glm/glm/gtc/type_ptr.hpp>

/**
 * @brief Klasa reprezentuj¹ca szeœcian.
 * 
 * Dziedziczy po klasie Primitive i implementuje metodê rysowania szeœcianu.
 */
class Cube : public Primitive {
private:
    /** 
     * @brief Wektor przechowuj¹cy indeksy wierzcho³ków szeœcianu.
	 */
    std::vector<GLuint> indices;

public:
    /**
     * @brief Konstruktor klasy Cube.
     *
     * Inicjalizuje wierzcho³ki i indeksy szeœcianu o podanym rozmiarze.
     * 
     * @param size Rozmiar krawêdzi szeœcianu.
	 */
    Cube(float size = 1.0f);
    /**
     * @brief Wirtualny destruktor klasy Cube.
	 */
    void draw() override;
};

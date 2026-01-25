/**
 * @file TexturedCube.h
 * @brief Klasa reprezentuj¹ca teksturowany model szeœcianu.
 */

#pragma once
#include "Primitive.h"

 /**
  * @class TexturedCube
  * @brief Klasa definiuj¹ca szeœcian z na³o¿on¹ tekstur¹.
  *
  * Dziedziczy po klasie Primitive i implementuje specyficzne dla szeœcianu
  * buforowanie wierzcho³ków oraz nak³adanie wspó³rzêdnych tekstur.
  */

class TexturedCube : public Primitive {
private:
    /** @brief Wektor indeksów wierzcho³ków do renderowania */
    std::vector<GLuint> indices;
    /** @brief Identyfikator tekstury OpenGL przypisanej do szeœcianu */
    GLuint textureID;
public:
    /**
   * @brief Konstruktor tworz¹cy model szeœcianu.
   *
   * Inicjalizuje geometriê szeœcianu o zadanych wymiarach i przypisuje teksturê.
   *
   * @param size D³ugoœæ boku szeœcianu.
   * @param texID Identyfikator za³adowanej wczeœniej tekstury OpenGL.
   */

    TexturedCube(float size, GLuint texID);

    /**
     * @brief Renderuje szeœcian na ekranie.
     *
     * Nadpisuje metodê draw z klasy bazowej. Odpowiada za bindowanie tekstury
     * oraz wywo³anie poleceñ rysuj¹cych OpenGL.
     */
    void draw() override;
}; 

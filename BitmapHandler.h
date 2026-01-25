/**
 * @file BitmapHandler.h
 * @brief Klasa narzêdziowa do obs³ugi plików graficznych i tekstur OpenGL.
 */

#pragma once
#include "glew/include/GL/glew.h"
#include <string>

 /**
  * @class BitmapHandler
  * @brief Statyczna klasa odpowiedzialna za ³adowanie obrazów i tworzenie tekstur OpenGL.
  *
  * Klasa wykorzystuje bibliotekê stb_image do odczytu danych binarnych z plików
  * i przesy³ania ich do pamiêci karty graficznej.
  */

class BitmapHandler {
public:
    /**
   * @brief £aduje plik graficzny i tworzy z niego teksturê OpenGL.
   *
   * Funkcja automatycznie odwraca obraz pionowo (flip), generuje mipmapy
   * oraz ustawia parametry filtrowania na GL_LINEAR.
   *
   * @param filename Œcie¿ka do pliku graficznego.
   * @return GLuint Identyfikator wygenerowanej tekstury OpenGL. Zwraca 0 w przypadku b³êdu.
   */
 
    static GLuint loadTexture(const std::string& filename);
};
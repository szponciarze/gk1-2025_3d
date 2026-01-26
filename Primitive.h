/**
 * @file Primitive.h
 * @brief Klasa bazowa dla prymitywnych obiektów 3D.
 */



#pragma once
#include <vector>
#include <SDL_opengl.h>
#include "ShapeObject.h"

/**
 * @struct Vertex
 * @brief Struktura reprezentuj¹ca pojedynczy wierzcho³ek obiektu 3D.
 *
 * Zawiera informacje o pozycji, normalnej, kolorze i wspó³rzêdnych tekstury wierzcho³ka.
 */
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;  
    glm::vec3 color; 
	glm::vec2 texCoords;    

    Vertex(const glm::vec3& pos,
        const glm::vec3& norm,
        const glm::vec3& col,
        const glm::vec2& tex = glm::vec2(0.0f, 0.0f))
        : position(pos), normal(norm), color(col), texCoords(tex) {
    }
};
/**
 * @class Primitive
 * @brief Klasa bazowa dla prymitywnych obiektów 3D.
 *
 * Dziedziczy po ShapeObject i przechowuje kolekcjê wierzcho³ków definiuj¹cych kszta³t prymitywu.
 */
class Primitive : public ShapeObject {
protected:
    /** 
     * @brief Wektor przechowuj¹cy wierzcho³ki prymitywu.
	 */
    std::vector<Vertex> vertices;
public:
    /**
     * @brief Wirtualny destruktor klasy Primitive.
	 */
    virtual ~Primitive() = default;
};

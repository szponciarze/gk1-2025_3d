#pragma once
#include "Primitive.h"

/**
 * @brief Klasa reprezentuj¹ca wielok¹ty.
 * 
 * Dziedziczy po klasie Primitive i implementuje metodê rysowania wielok¹ta.
 */
class Polylines : public Primitive {
public:
    /**
     * @brief Konstruktor klasy Polylines.
     *
     * Inicjalizuje wielok¹t z podan¹ list¹ wierzcho³ków.
     * 
	 * @param verts Wektor wierzcho³ków tworz¹cych wielok¹t.
     * 
     **/
    Polylines(const std::vector<Vertex>& verts) { vertices = verts; }

    /**
	* @brief Implementacja metody rysowania wielok¹ta.
    **/
    void draw() override {
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(modelMatrix));

        glBegin(GL_LINE_STRIP);
        for (auto& v : vertices) {
            glNormal3f(v.normal.x, v.normal.y, v.normal.z);
            glColor3f(v.color.r, v.color.g, v.color.b);
            glVertex3f(v.position.x, v.position.y, v.position.z);
        }
        glEnd();
        glColor3f(1.0f, 1.0f, 1.0f);
        glPopMatrix();
    }
};

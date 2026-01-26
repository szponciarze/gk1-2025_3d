/**
 * @file Line.h
 * @brief Klasa reprezentuj¹ca liniê.
 */



#pragma once
#include "Primitive.h"

/**
 * @brief Klasa reprezentuj¹ca liniê.
 * 
 * Dziedziczy po klasie Primitive i implementuje metodê rysowania linii.
 */
class Line : public Primitive {
public:
    /**
     * @brief Konstruktor klasy Line.
     *
     * Inicjalizuje liniê z dwoma wierzcho³kami.
     * 
     * @param v1 Pierwszy wierzcho³ek linii.
     * @param v2 Drugi wierzcho³ek linii.
	 */
    Line(const Vertex& v1, const Vertex& v2) {
        vertices.push_back(v1);
        vertices.push_back(v2);
    }
    
    /**
	 * @brief Implementacja metody rysowania lini.
     **/
    void draw() override {
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(modelMatrix));

        glBegin(GL_LINES);
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

/**
 * @file Triangle.h
 * @brief Klasa reprezentuj¹ca trójk¹t.
 */



#pragma once
#include "Primitive.h"
/**
 * @brief Klasa reprezentuj¹ca trójk¹t.
 * 
 * Dziedziczy po klasie Primitive i implementuje metodê rysowania trójk¹ta.
 */
class Triangle : public Primitive {
public:
    /**
     * @brief Konstruktor klasy Triangle.
     *
     * Inicjalizuje trójk¹t z trzema wierzcho³kami.
     * 
     * @param v1 Pierwszy wierzcho³ek trójk¹ta.
     * @param v2 Drugi wierzcho³ek trójk¹ta.
     * @param v3 Trzeci wierzcho³ek trójk¹ta.
     * 
	 **/
    Triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) {
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
    }
    /**
	* @brief Implementacja metody rysowania trójk¹ta.
    **/
    void draw() override {
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(modelMatrix));

        glBegin(GL_TRIANGLES);
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

/**
 * @file TriangleStrip.h
 * @brief Klasa reprezentuj¹ca pasek trójk¹tów.
 */


#pragma once
#include "Primitive.h"
/**
 * @brief Klasa reprezentuj¹ca pasek trójk¹tów.
 * 
 * Dziedziczy po klasie Primitive i implementuje metodê rysowania paska trójk¹tów.
 */
class TriangleStrip : public Primitive {
public:
    /**
     * @brief Konstruktor klasy TriangleStrip.
     *
     * Inicjalizuje pasek trójk¹tów z podan¹ list¹ wierzcho³ków.
     * 
     * @param verts Wektor wierzcho³ków tworz¹cych pasek trójk¹tów.
	 *
     **/
    TriangleStrip(const std::vector<Vertex>& verts) { vertices = verts; }
    /**
	* @brief Implementacja metody rysowania paska trójk¹tów.
    **/
    void draw() override {
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(modelMatrix));

        glBegin(GL_TRIANGLE_STRIP);
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

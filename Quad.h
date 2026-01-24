#pragma once
#include "Primitive.h"
/**
 * @brief Klasa reprezentuj¹ca czworok¹t.
 * 
 * Dziedziczy po klasie Primitive i implementuje metodê rysowania czworok¹ta.
 */
class Quad : public Primitive {
public:
    /**
     * @brief Konstruktor klasy Quad.
     *
     * Inicjalizuje czworok¹t z czterema wierzcho³kami.
     * 
     * @param v1 Pierwszy wierzcho³ek czworok¹ta.
     * @param v2 Drugi wierzcho³ek czworok¹ta.
     * @param v3 Trzeci wierzcho³ek czworok¹ta.
	 * @param v4 Czwarty wierzcho³ek czworok¹ta.
     * 
     **/ 
    Quad(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4) {
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
        vertices.push_back(v4);
    }
    /**
	* @brief Implementacja metody rysowania czworok¹ta.
    **/
    void draw() override {
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(modelMatrix));

        glBegin(GL_QUADS);
        
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

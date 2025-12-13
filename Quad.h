#pragma once
#include "Primitive.h"

class Quad : public Primitive {
public:
    Quad(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4) {
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
        vertices.push_back(v4);
    }

    void draw() override {
        glBegin(GL_QUADS);
        for (auto& v : vertices) {
            glColor3f(v.color.r, v.color.g, v.color.b);
            glVertex3f(v.position.x, v.position.y, v.position.z);
        }
        glEnd();
    }

};

#pragma once
#include "Primitive.h"

class Line : public Primitive {
public:
    Line(const Vertex& v1, const Vertex& v2) {
        vertices.push_back(v1);
        vertices.push_back(v2);
    }
    void draw() override {
        glBegin(GL_LINES);
        for (auto& v : vertices) {
            glColor3f(v.color.r, v.color.g, v.color.b);
            glVertex3f(v.position.x, v.position.y, v.position.z);
        }
        glEnd();
    }
};

#pragma once
#include "Primitive.h"

class Point : public Primitive {
public:
    Point(const Vertex& v) { vertices.push_back(v); }
    void draw() override {
        glBegin(GL_POINTS);
        for (auto& v : vertices) {
            glColor3f(v.color.r, v.color.g, v.color.b);
            glVertex3f(v.position.x, v.position.y, v.position.z);
        }
        glEnd();
    }
};

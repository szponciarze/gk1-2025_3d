#pragma once
#include "Primitive.h"

class Triangle : public Primitive {
public:
    Triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) {
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
    }
    void draw() override {
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(modelMatrix));

        glBegin(GL_TRIANGLES);
        for (auto& v : vertices) {
            glColor3f(v.color.r, v.color.g, v.color.b);
            glVertex3f(v.position.x, v.position.y, v.position.z);
        }
        glEnd();

        glPopMatrix();
    }
};

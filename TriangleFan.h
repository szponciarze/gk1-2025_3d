#pragma once
#include "Primitive.h"

class TriangleFan : public Primitive {
public:
    TriangleFan(const std::vector<Vertex>& verts) { vertices = verts; }
    void draw() override {
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(modelMatrix));

        glBegin(GL_TRIANGLE_FAN);
        for (auto& v : vertices) {
            glColor3f(v.color.r, v.color.g, v.color.b);
            glVertex3f(v.position.x, v.position.y, v.position.z);
        }
        glEnd();

        glPopMatrix();
    }
};

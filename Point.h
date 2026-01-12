#pragma once
#include "Primitive.h"

class Point : public Primitive {
public:
    Point(const Vertex& v) { vertices.push_back(v); }
    void draw() override {
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(modelMatrix));

        glBegin(GL_POINTS);
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

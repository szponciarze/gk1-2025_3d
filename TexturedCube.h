#pragma once
#include "Primitive.h"

class TexturedCube : public Primitive {
private:
    std::vector<GLuint> indices;
    GLuint textureID;
public:
    TexturedCube(float size, GLuint texID);
    void draw() override;
}; 

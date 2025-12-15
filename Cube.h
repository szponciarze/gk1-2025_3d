#pragma once
#include "Primitive.h"
#include <vector>
#include <SDL_opengl.h>

class Cube : public Primitive {
private:
    std::vector<GLuint> indices;

public:
    Cube(float size = 1.0f);
    void draw() override;
};

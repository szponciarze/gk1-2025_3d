#pragma once
#include <vector>
#include <SDL_opengl.h>
#include "ShapeObject.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    Vertex(const glm::vec3& pos, const glm::vec3& col) : position(pos), color(col) {}
};

class Primitive : public ShapeObject {
protected:
    std::vector<Vertex> vertices;
public:
    virtual ~Primitive() = default;
};

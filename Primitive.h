#pragma once
#include <vector>
#include <glm/glm/glm.hpp>
#include <SDL_opengl.h>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    Vertex(const glm::vec3& pos, const glm::vec3& col) : position(pos), color(col) {}
};

class Primitive {
protected:
    std::vector<Vertex> vertices;
public:
    virtual void draw() = 0;
};

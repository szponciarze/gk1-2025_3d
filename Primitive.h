#pragma once
#include <vector>
#include <SDL_opengl.h>
#include "ShapeObject.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;  
    glm::vec3 color; 
	glm::vec2 texCoords;    

    Vertex(const glm::vec3& pos,
        const glm::vec3& norm,
        const glm::vec3& col,
        const glm::vec2& tex = glm::vec2(0.0f, 0.0f))
        : position(pos), normal(norm), color(col), texCoords(tex) {
    }
};

class Primitive : public ShapeObject {
protected:
    std::vector<Vertex> vertices;
public:
    virtual ~Primitive() = default;
};

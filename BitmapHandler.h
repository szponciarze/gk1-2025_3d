#pragma once
#include "glew/include/GL/glew.h"
#include <string>

class BitmapHandler {
public:
 
    static GLuint loadTexture(const std::string& filename);
};
#include "Cube.h"

Cube::Cube(float size) {
    float h = size / 2.0f;

   
    vertices = {
        {{-h,-h,-h}, {1,0,0}}, 
        {{ h,-h,-h}, {0,1,0}}, 
        {{ h, h,-h}, {0,0,1}}, 
        {{-h, h,-h}, {1,1,0}}, 
        {{-h,-h, h}, {0,1,1}}, 
        {{ h,-h, h}, {1,0,1}}, 
        {{ h, h, h}, {1,1,1}}, 
        {{-h, h, h}, {0,0,0}} 
    };

    
    normals = {
        { 0, 0,-1}, 
        { 0, 0, 1}, 
        {-1, 0, 0}, 
        { 1, 0, 0}, 
        { 0,-1, 0}, 
        { 0, 1, 0}  
    };


    indices = {
        0,1,2, 2,3,0,
        4,5,6, 6,7,4,
        0,3,7, 7,4,0,
        1,5,6, 6,2,1,
        0,4,5, 5,1,0,
        3,2,6, 6,7,3
    };
}

void Cube::draw() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(
        3,
        GL_FLOAT,
        sizeof(Vertex),
        &vertices[0].position
    );

    glColorPointer(
        3,
        GL_FLOAT,
        sizeof(Vertex),
        &vertices[0].color
    );

    glDrawElements(
        GL_TRIANGLES,
        indices.size(),
        GL_UNSIGNED_INT,
        indices.data()
    );

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

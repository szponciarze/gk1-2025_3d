#include "Cube.h"

Cube::Cube(float size)
{
    float h = size / 2.0f;

    vertices = {
        {{-h,-h, h}, {0,0,1}, {1,0,0}},
        {{ h,-h, h}, {0,0,1}, {1,0,0}},
        {{ h, h, h}, {0,0,1}, {1,0,0}},
        {{-h, h, h}, {0,0,1}, {1,0,0}},

        
        {{ h,-h,-h}, {0,0,-1}, {0,1,0}},
        {{-h,-h,-h}, {0,0,-1}, {0,1,0}},
        {{-h, h,-h}, {0,0,-1}, {0,1,0}},
        {{ h, h,-h}, {0,0,-1}, {0,1,0}},

      
        {{-h,-h,-h}, {-1,0,0}, {0,0,1}},
        {{-h,-h, h}, {-1,0,0}, {0,0,1}},
        {{-h, h, h}, {-1,0,0}, {0,0,1}},
        {{-h, h,-h}, {-1,0,0}, {0,0,1}},

        
        {{ h,-h, h}, {1,0,0}, {1,1,0}},
        {{ h,-h,-h}, {1,0,0}, {1,1,0}},
        {{ h, h,-h}, {1,0,0}, {1,1,0}},
        {{ h, h, h}, {1,0,0}, {1,1,0}},

      
        {{-h, h, h}, {0,1,0}, {1,0,1}},
        {{ h, h, h}, {0,1,0}, {1,0,1}},
        {{ h, h,-h}, {0,1,0}, {1,0,1}},
        {{-h, h,-h}, {0,1,0}, {1,0,1}},

       
        {{-h,-h,-h}, {0,-1,0}, {0,1,1}},
        {{ h,-h,-h}, {0,-1,0}, {0,1,1}},
        {{ h,-h, h}, {0,-1,0}, {0,1,1}},
        {{-h,-h, h}, {0,-1,0}, {0,1,1}},
    };

    indices = {
        0,1,2, 2,3,0,
        4,5,6, 6,7,4,
        8,9,10, 10,11,8,
        12,13,14, 14,15,12,
        16,17,18, 18,19,16,
        20,21,22, 22,23,20
    };
}

void Cube::draw()
{
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(modelMatrix));

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &vertices[0].position);
    glNormalPointer(GL_FLOAT, sizeof(Vertex), &vertices[0].normal);
    glColorPointer(3, GL_FLOAT, sizeof(Vertex), &vertices[0].color);

    glDrawElements(
        GL_TRIANGLES,
        indices.size(),
        GL_UNSIGNED_INT,
        indices.data()
    );

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}

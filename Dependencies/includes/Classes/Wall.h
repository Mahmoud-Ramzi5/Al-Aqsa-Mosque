#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Wall
{
public:
    unsigned int VBO, VAO;
    unsigned int textureWall;
    // world space positions of our cubes
    float angle = 90.0f;

    float vertices[288] = {
        // positions          // normals         // texCoords
        -0.5f,  0.0f, -0.25f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,
         0.5f,  0.0f, -0.25f,  1.0f, 1.0f, 0.0f,  3.0f, 0.0f,
         0.5f,  1.5f, -0.25f,  1.0f, 1.0f, 0.0f,  3.0f, 1.0f,
         0.5f,  1.5f, -0.25f,  1.0f, 1.0f, 0.0f,  3.0f, 1.0f,
        -0.5f,  1.5f, -0.25f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        -0.5f,  0.0f, -0.25f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,

        -0.5f,  0.0f,  0.25f,  -1.0f, 1.0f, 0.0f,  0.0f, 0.0f,
         0.5f,  0.0f,  0.25f,  -1.0f, 1.0f, 0.0f,  3.0f, 0.0f,
         0.5f,  1.5f,  0.25f,  -1.0f, 1.0f, 0.0f,  3.0f, 1.0f,
         0.5f,  1.5f,  0.25f,  -1.0f, 1.0f, 0.0f,  3.0f, 1.0f,
        -0.5f,  1.5f,  0.25f,  -1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        -0.5f,  0.0f,  0.25f,  -1.0f, 1.0f, 0.0f,  0.0f, 0.0f,

        -0.5f,  1.5f,  0.25f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f,  1.5f, -0.25f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        -0.5f,  0.0f, -0.25f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        -0.5f,  0.0f, -0.25f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        -0.5f,  0.0f,  0.25f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
        -0.5f,  1.5f,  0.25f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,

         0.5f,  1.5f,  0.25f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
         0.5f,  1.5f, -0.25f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
         0.5f,  0.0f, -0.25f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
         0.5f,  0.0f, -0.25f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
         0.5f,  0.0f,  0.25f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
         0.5f,  1.5f,  0.25f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,

        -0.5f,  0.0f, -0.25f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
         0.5f,  0.0f, -0.25f,  0.0f, 1.0f, 0.0f,  3.0f, 1.0f,
         0.5f,  0.0f,  0.25f,  0.0f, 1.0f, 0.0f,  3.0f, 0.0f,
         0.5f,  0.0f,  0.25f,  0.0f, 1.0f, 0.0f,  3.0f, 0.0f,
        -0.5f,  0.0f,  0.25f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
        -0.5f,  0.0f, -0.25f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,

        -0.5f,  1.5f, -0.25f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
         0.5f,  1.5f, -0.25f,  0.0f, 1.0f, 0.0f,  3.0f, 1.0f,
         0.5f,  1.5f,  0.25f,  0.0f, 1.0f, 0.0f,  3.0f, 0.0f,
         0.5f,  1.5f,  0.25f,  0.0f, 1.0f, 0.0f,  3.0f, 0.0f,
        -0.5f,  1.5f,  0.25f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
        -0.5f,  1.5f, -0.25f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f
    };

    Wall(unsigned int texture);
    void DrawWall(unsigned int shaderId, int i);
};


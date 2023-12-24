#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Wall
{
public:
    unsigned int VBO, VAO;
    unsigned int textureWall;

    float vertices[180] = {
        -0.5f, -0.5f, -0.1f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.1f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.1f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.1f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.1f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.1f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.1f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.1f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.1f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.1f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.1f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.1f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.1f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.1f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.1f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.1f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.1f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.1f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.1f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.1f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.1f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.1f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.1f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.1f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.1f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.1f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.1f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.1f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.1f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.1f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.1f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.1f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.1f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.1f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.1f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.1f,  0.0f, 1.0f
    };
    // world space positions of our cubes
    float angle = 90.0f;
    glm::vec3 WallPositions[4] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(0.0f,  0.0f, -1.0f),
        glm::vec3(0.6f,0.0f,-0.4f),
        glm::vec3(-0.6f,0.0f,-0.4f)
    };

    Wall(unsigned int texture);
    void DrawWall(unsigned int shaderId, int i);
};


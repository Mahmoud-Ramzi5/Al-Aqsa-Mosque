#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Qubli
{
public:
    unsigned int VBO, VAO, EBO;
    unsigned int textureQubli;
    
    float vertices[80] = {
        // positions          // normals          // texture coords
        -0.5f, 0.0f, -0.7f,     0.0f, 1.0f, 0.0f,    0.0f, 0.0f,  
         0.5f, 0.0f, -0.7f,     0.0f, 1.0f, 0.0f,    0.304f, 0.0f,
         0.5f, 0.0f , 0.7f,     0.0f, 1.0f, 0.0f,    0.592f, 0.0f,
        -0.5f, 0.0f , 0.7f,     0.0f, 1.0f, 0.0f,    0.712f, 0.0f,

        // positions          // normals         // texture coords
        -0.5f, 0.2f, -0.7f,     0.0f, 1.0f, 0.0f,    0.0f, 1.0f,  
         0.5f, 0.2f, -0.7f,     0.0f, 1.0f, 0.0f,    0.304f, 1.0f,
         0.5f, 0.2f,  0.7f,     0.0f, 1.0f, 0.0f,    0.592f, 1.0f,
        -0.5f, 0.2f,  0.7f,     0.0f, 1.0f, 0.0f,    0.712f, 1.0f,
        
        -0.5f, 0.0f, -0.7f,     0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
        -0.5f, 0.2f, -0.7f,     0.0f, 1.0f, 0.0f,    1.0f, 1.0f,
    };

    unsigned int indices[36] = {
       0, 1, 2,
       2, 3, 0,

       4, 5, 6,
       6, 7, 4,

      // Sides
       0, 1, 4,
       4, 1, 5,

       1, 2, 5,
       5, 2, 6,

       2, 3, 6,
       6, 3, 7,

       3, 8, 7,
       7, 8, 9,
    };

    Qubli(unsigned int texture);
    float* GetVertices();
    unsigned int* GetIndices();
    void DrawQubli();
};

#pragma once

class Qubli
{
public:
    unsigned int VBO, VAO, EBO;
    unsigned int textureQubli;

    float vertices[80] = {
        //masjid
        // positions          // colors          // texture coords
        -0.5f, 0.0f, -0.7f,     0.0f, 1.0f, 0.0f,    0.0f, 0.0f,             // Bottom-left vertex
         0.5f, 0.0f, -0.7f,     0.0f, 1.0f, 0.0f,    0.304f, 0.0f,            // Bottom-right vertex
         0.5f, 0.0f , 0.7f,     0.0f, 1.0f, 0.0f,    0.592f, 0.0f,           // Top-right vertex
        -0.5f, 0.0f , 0.7f,     0.0f, 1.0f, 0.0f,    0.712f, 0.0f,          // Top-left vertex

        // positions          // colors         // texture coords
        -0.5f, 0.2f, -0.7f,     0.0f, 1.0f, 0.0f,    0.0f, 1.0f,        // Bottom-left vertex
         0.5f, 0.2f, -0.7f,     0.0f, 1.0f, 0.0f,    0.304f, 1.0f,       // Bottom-right vertex
         0.5f, 0.2f,  0.7f,     0.0f, 1.0f, 0.0f,    0.592f, 1.0f,      // Top-right vertex
        -0.5f, 0.2f,  0.7f,     0.0f, 1.0f, 0.0f,    0.712f, 1.0f,     // Top-left vertex
        
        -0.5f, 0.0f, -0.7f,     0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
        -0.5f, 0.2f, -0.7f,     0.0f, 1.0f, 0.0f,    1.0f, 1.0f,
    };

    unsigned int indices[36] = {
       0, 1, 2,  // First triangle
       2, 3, 0,

       4, 5, 6, // Second triangle
       6, 7, 4,
       //sides
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

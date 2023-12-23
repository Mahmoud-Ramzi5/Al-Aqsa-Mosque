#pragma once

class Qubli
{
public:
    unsigned int VBO, VAO, EBO;
    unsigned int textureQubli;

    float vertices[64] = {
        //masjid
        // positions          // colors          // texture coords
        -0.7f, 0.0f,      -0.5f,0.0f,1.0f,0.0f,    0.0f, 0.0f,             // Bottom-left vertex
         0.7f, 0.0f,      -0.5f,0.0f,1.0f,0.0f,    0.0f, 0.0f,            // Bottom-right vertex
         0.7f, 0.0f ,      0.5f,0.0f,1.0f,0.0f,    0.0f, 0.0f,           // Top-right vertex
        -0.7f, 0.0f ,      0.5f,0.0f,1.0f,0.0f,    0.0f, 0.0f,          // Top-left vertex

        // positions          // colors         // texture coords
        -0.7f, 0.2f,      -0.5f,0.0f,1.0f,0.0f,    0.0f, 0.0f,        // Bottom-left vertex
         0.7f, 0.2f,      -0.5f,0.0f,1.0f,0.0f,    0.0f, 0.0f,       // Bottom-right vertex
         0.7f, 0.2f,       0.5f,0.0f,1.0f,0.0f,    0.0f, 0.0f,      // Top-right vertex
        -0.7f, 0.2f,       0.5f,0.0f,1.0f,0.0f,    0.0f, 0.0f,     // Top-left vertex
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
       3, 0, 7,
       7, 0, 4,
    };

    Qubli(unsigned int texture);
    float* GetVertices();
    unsigned int* GetIndices();
    void DrawQubli();
};

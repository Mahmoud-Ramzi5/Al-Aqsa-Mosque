#pragma once

class Skyscrapper
{
public:
    unsigned int VBO, VAO, EBO;
    unsigned int textureSkyscrapper;

    float vertices[80] = {
        // positions            // normals          // texture coords
        -0.5f, 0.0f, -0.7f,     0.0f, 1.0f, 0.0f,    0.0f, 0.0f,
         0.5f, 0.0f, -0.7f,     0.0f, 1.0f, 0.0f,    0.264f, 0.0f,
         0.5f, 0.0f , 0.7f,     0.0f, 1.0f, 0.0f,    0.507f, 0.0f,
        -0.5f, 0.0f , 0.7f,     0.0f, 1.0f, 0.0f,    0.757f, 0.0f,

        // positions            // normals         // texture coords
        -0.5f, 2.0f, -0.7f,     0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
         0.5f, 2.0f, -0.7f,     0.0f, 1.0f, 0.0f,    0.264f, 1.0f,
         0.5f, 2.0f,  0.7f,     0.0f, 1.0f, 0.0f,    0.507f, 1.0f,
        -0.5f, 2.0f,  0.7f,     0.0f, 1.0f, 0.0f,    0.757f, 1.0f,

        -0.5f, 0.0f, -0.7f,     0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
        -0.5f, 2.0f, -0.7f,     0.0f, 1.0f, 0.0f,    1.0f, 1.0f,
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

    Skyscrapper(unsigned int texture);
    float* GetVertices();
    unsigned int* GetIndices();
    void DrawSkyscrapper();
};


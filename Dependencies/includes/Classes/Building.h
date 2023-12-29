#pragma once

class Building
{
public:
    unsigned int VBO, VAO, EBO;
    unsigned int textureBuilding;

    float vertices[80] = {
        // positions            // normals          // texture coords
        -0.5f, 0.0f, -0.7f,     0.0f, 1.0f, 0.0f,    0.0f, 0.0f,
         0.5f, 0.0f, -0.7f,     0.0f, 1.0f, 0.0f,    0.267f, 0.0f,
         0.5f, 0.0f , 0.7f,     0.0f, 1.0f, 0.0f,    0.498f, 0.0f,
        -0.5f, 0.0f , 0.7f,     0.0f, 1.0f, 0.0f,    0.769f, 0.0f,

        // positions            // normals         // texture coords
        -0.5f, 1.0f, -0.7f,     0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
         0.5f, 1.0f, -0.7f,     0.0f, 1.0f, 0.0f,    0.267f, 1.0f,
         0.5f, 1.0f,  0.7f,     0.0f, 1.0f, 0.0f,    0.498f, 1.0f,
        -0.5f, 1.0f,  0.7f,     0.0f, 1.0f, 0.0f,    0.769f, 1.0f,

        -0.5f, 0.0f, -0.7f,     0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
        -0.5f, 1.0f, -0.7f,     0.0f, 1.0f, 0.0f,    1.0f, 1.0f,
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

    Building(unsigned int texture);
    float* GetVertices();
    unsigned int* GetIndices();
    void DrawBuilding();
};

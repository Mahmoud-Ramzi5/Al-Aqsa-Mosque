#pragma once

class Floor
{
public:
    unsigned int VBO, VAO, EBO;
    unsigned int textureOct;

    float vertices[32] {
        5.0f, 0.0035f,  7.0f,   0.0f, 1.0f, 0.0f,  10.0f, 0.0f,
        5.0f, 0.0035f, -7.0f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
       -5.0f, 0.0035f,  7.0f,   0.0f, 1.0f, 0.0f,  10.0f, 10.0f,
       -5.0f, 0.0035f, -7.0f,   0.0f, 1.0f, 0.0f,  0.0f, 10.0f
    };

    unsigned int indices[6] {
        0, 1, 2,
        1, 2, 3
    };

    Floor(unsigned int texture);
    float* GetVertices();
    unsigned int* GetIndices();
    void DrawFloor();
};


#pragma once

class Rug
{
public:
    unsigned int VBO, VAO, EBO;
    unsigned int textureOct;

    float vertices[32]{
        1.0f, 0.0035f,  1.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        1.0f, 0.0035f, -1.0f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
       -1.0f, 0.0035f,  1.0f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
       -1.0f, 0.0035f, -1.0f,   0.0f, 1.0f, 0.0f,  0.0f, 1.0f
    };

    unsigned int indices[6]{
        0, 1, 2,
        1, 2, 3
    };

    Rug(unsigned int texture);
    float* GetVertices();
    unsigned int* GetIndices();
    void DrawRug();
};


#pragma once
class Singlewall
{
public:
    unsigned int VBO, VAO, EBO;
    unsigned int textureOct;

    float vertices[32]{
        1.0f, 0.0035f,  0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        1.0f, 2.0035f,  0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
       -0.0f, 0.0035f,  0.0f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
       -0.0f, 2.0035f,  0.0f,   0.0f, 1.0f, 0.0f,  0.0f, 1.0f
    };

    unsigned int indices[6]{
        2, 3, 1,
        1, 0, 2
    };

    Singlewall(unsigned int texture);
    float* GetVertices();
    unsigned int* GetIndices();
    void DrawSinglewall();
};
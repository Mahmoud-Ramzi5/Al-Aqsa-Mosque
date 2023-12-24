#pragma once
class Octagon
{
public:
    unsigned int VBO, VAO, EBO;
    unsigned int textureOct;

    float vertices[208] = {
        // positions          // colors           // texture coords
        0.0f,  0.0f, 1.0f,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f,   // Vertex 0

        0.7f, 0.0f, 0.7f,   0.0f, 1.0f, 0.0f,   0.125f, 0.0f, // Vertex 1
        1.0f,  0.0f, 0.0f,    0.0f, 1.0f, 0.0f,   0.250f, 0.0f, // Vertex 2
        0.7f, 0.0f, -0.7f,  0.0f, 1.0f, 0.0f,   0.375f, 0.0f, // Vertex 3
        0.0f, 0.0f, -1.0f,    0.0f, 1.0f, 0.0f,   0.500f, 0.0f, // Vertex 4
       -0.7f, 0.0f, -0.7f,  0.0f, 1.0f, 0.0f,   0.625f, 0.0f, // Vertex 5
       -1.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.750f, 0.0f, // Vertex 6
       -0.7f, 0.0f, 0.7f,   0.0f, 1.0f, 0.0f,   0.875f, 0.0f, // Vertex 7

        0.0f, 0.0f, 1.0f,     0.0f ,1.0f, 0.0f,   1.0f, 0.0f,   // Vertex 8 (same as the Vertex 0 to close the shape)

        // positions          // colors           // texture coords
        0.0f, 0.5f, 1.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.5f,   // vertex 9

        0.7f, 0.5f, 0.7f,   0.0f, 1.0f, 0.0f,   0.125f, 0.5f, // Vertex 10
        1.0f, 0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   0.250f, 0.5f, // Vertex 11
        0.7f, 0.5f, -0.7f,  0.0f, 1.0f, 0.0f,   0.375f, 0.5f, // Vertex 12
        0.0f, 0.5f, -1.0f,    0.0f, 1.0f, 0.0f,   0.500f, 0.5f, // Vertex 13
       -0.7f, 0.5f, -0.7f,  0.0f, 1.0f, 0.0f,   0.625f, 0.5f, // Vertex 14
       -1.0f, 0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   0.750f, 0.5f, // Vertex 15
       -0.7f, 0.5f, 0.7f,   0.0f, 1.0f, 0.0f,   0.875f, 0.5f, // Vertex 16

        0.0f, 0.5f, 1.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.5f,   // Vertex 17 (same as the Vertex 8 to close the shape)

        // middle of octagon (repeated just for textures coords)
        0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 0.0f,  0.0625f, 1.0f,
        0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 0.0f,  0.1875f, 1.0f,
        0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 0.0f,  0.3125f, 1.0f,
        0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 0.0f,  0.4375f, 1.0f,
        0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 0.0f,  0.5625f, 1.0f,
        0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 0.0f,  0.6875f, 1.0f,
        0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 0.0f,  0.8125f, 1.0f,
        0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 0.0f,  0.9375f, 1.0f,
    };

    unsigned int indices[72] = {
        // Sides (From Front Reverse Clock-Wise)
        0, 9, 10,
        10, 1, 0,

        1, 10, 11,
        11, 2, 1,

        2, 11, 12,
        12, 3, 2,

        3, 12, 13,
        13, 4, 3,

        4, 13, 14,
        14, 5, 4,

        5, 14, 15,
        15, 6, 5,

        6, 15, 16,
        16, 7, 6,

        7, 16, 17,
        17, 8, 7,

        // Top Face
        9, 18, 10,

        10, 19, 11,

        11, 20, 12,

        12, 21, 13,

        13, 22, 14,

        14, 23, 15,

        15, 24, 16,

        16, 25, 17

    };

    Octagon(unsigned int texture);
    float* GetVertices();
    unsigned int* GetIndices();
    void DrawOct();
};


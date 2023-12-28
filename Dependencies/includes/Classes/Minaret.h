#pragma once
class Minaret
{
public:
    unsigned int VBO, VAO, EBO;
    unsigned int textureOct;

    float vertices[208] = {
        // positions          // colors           // texture coords
       // positions          // colors          // texture coords
        -0.2f, 0.0f, -0.2f,    -1.0f, 1.0f, 0.0f,    0.0f, 0.0f,
         0.2f, 0.0f, -0.2f,    -1.0f, 1.0f, 0.0f,    0.25f, 0.0f,
         0.2f, 0.0f , 0.2f,    -1.0f, 1.0f, 0.0f,    0.5f, 0.0f,
        -0.2f, 0.0f , 0.2f,    -1.0f, 1.0f, 0.0f,    0.75f, 0.0f,

        // positions          // colors         // texture coords
        -0.2f, 2.0f, -0.2f,     0.0f, 1.0f, 0.0f,    0.0f, 0.87f,
         0.2f, 2.0f, -0.2f,     0.0f, 1.0f, 0.0f,    0.25f, 0.87f,
         0.2f, 2.0f,  0.2f,     0.0f, 1.0f, 0.0f,    0.5f, 0.87f,
        -0.2f, 2.0f,  0.2f,     0.0f, 1.0f, 0.0f,    0.75f, 0.87f,

        -0.2f, 0.0f, -0.2f,     -1.0f, 1.0f, 0.0f,    1.0f, 0.0f,
        -0.2f, 2.0f, -0.2f,     0.0f, 1.0f, 0.0f,    1.0f, 0.87f,

         0.0f, 3.0f, 0.0f,      0.0f, 1.0f, 0.0f,    0.125f, 1.0f,
         0.0f, 3.0f, 0.0f,      0.0f, 1.0f, 0.0f,    0.375f, 1.0f,
         0.0f, 3.0f, 0.0f,      0.0f, 1.0f, 0.0f,    0.625f, 1.0f,
         0.0f, 3.0f, 0.0f,      0.0f, 1.0f, 0.0f,    0.875f, 1.0f,
    };

    unsigned int indices[48] = {
      0, 1, 2,
      2, 3, 0,

      4, 5, 6,
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

      4, 10, 5,
      5, 11, 6,
      6, 12, 7,
      7, 13, 9
    };

    Minaret(unsigned int texture);
    float* GetVertices();
    unsigned int* GetIndices();
    void DrawMinaret();
};
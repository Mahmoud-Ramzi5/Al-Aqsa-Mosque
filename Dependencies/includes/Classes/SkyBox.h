#pragma once
class SkyBox
{
public:
    unsigned int VBO, VAO, EBO;
    unsigned int textureSky[6];

    float SkyboxVertices[180] = {
        // positions           // texCoords
       // roof
        -50.0f,  50.0f, -50.0f,     0.0f, 0.0f,
        -50.0f,  50.0f,  50.0f,     0.0f, 1.0f,
         50.0f,  50.0f,  50.0f,     1.0f, 1.0f,
         50.0f,  50.0f,  50.0f,     1.0f, 1.0f,
         50.0f,  50.0f, -50.0f,     1.0f, 0.0f,
        -50.0f,  50.0f, -50.0f,     0.0f, 0.0f,
        
        // sides
        -50.0f,  0.0f,   50.0f,     0.0f, 0.25f,
        -50.0f,  0.0f,  -50.0f,     0.25f, 0.25f,
         50.0f,  0.0f,  -50.0f,     0.50f, 0.25f,
         50.0f,  0.0f,   50.0f,     0.75f, 0.25f,
        -50.0f,  0.0f,   50.0f,     1.0f, 0.25f,

        -50.0f,  50.0f,   50.0f,     0.0f, 1.0f,
        -50.0f,  50.0f,  -50.0f,     0.25f, 1.0f,
         50.0f,  50.0f,  -50.0f,     0.50f, 1.0f,
         50.0f,  50.0f,   50.0f,     0.75f, 1.0f,
        -50.0f,  50.0f,   50.0f,     1.0f, 1.0f,

        // floor
        -50.0f,  -0.0f, -50.0f,      0.0f, 0.0f,
        -50.0f,  -0.0f,  50.0f,      0.0f, 1.0f,
         50.0f,  -0.0f,  50.0f,      1.0f, 1.0f,
         50.0f,  -0.0f,  50.0f,      1.0f, 1.0f,
         50.0f,  -0.0f, -50.0f,      1.0f, 0.0f,
        -50.0f,  -0.0f, -50.0f,      0.0f, 0.0f,
        /*
        // back face
        -50.0f,  0.0f,  -50.0f,     0.0f, 0.0f,
         50.0f,  0.0f,  -50.0f,     1.0f, 0.0f,
         50.0f,  50.0f, -50.0f,     1.0f, 1.0f,
         50.0f,  50.0f, -50.0f,     1.0f, 1.0f,
        -50.0f,  50.0f, -50.0f,     0.0f, 1.0f,
        -50.0f,  0.0f,  -50.0f,     0.0f, 0.0f,

        // left face
        -50.0f,  0.0f,  -50.0f,     0.0f, 0.0f,
        -50.0f,  0.0f,   50.0f,     0.0f, 1.0f,
        -50.0f,  50.0f,  50.0f,     1.0f, 1.0f,
        -50.0f,  50.0f,  50.0f,     1.0f, 1.0f,
        -50.0f,  50.0f, -50.0f,     1.0f, 0.0f,
        -50.0f,  0.0f,  -50.0f,     0.0f, 0.0f,

        // right face
         50.0f,  0.0f,  -50.0f,     0.0f, 0.0f,
         50.0f,  0.0f,   50.0f,     0.0f, 1.0f,
         50.0f,  50.0f,  50.0f,     1.0f, 1.0f,
         50.0f,  50.0f,  50.0f,     1.0f, 1.0f,
         50.0f,  50.0f, -50.0f,     1.0f, 0.0f,
         50.0f,  0.0f,  -50.0f,     0.0f, 0.0f,

         // Front face
        -50.0f,  0.0f,  50.0f,      0.0f, 0.0f,
         50.0f,  0.0f,  50.0f,      1.0f, 0.0f,
         50.0f,  50.0f, 50.0f,      1.0f, 1.0f,
         50.0f,  50.0f, 50.0f,      1.0f, 1.0f,
        -50.0f,  50.0f, 50.0f,      0.0f, 1.0f,
        -50.0f,  0.0f,  50.0f,      0.0f, 0.0f,
        */
    };

    unsigned int indices[72] = {
        // Sides (From Front Reverse Clock-Wise)
        6, 11, 7,
        7, 12, 11,

        7, 12, 8,
        8, 13, 12,

        8, 13, 9, 
        9, 14, 13,
        
        9, 14, 10,
        10, 15, 14
    };

    SkyBox(unsigned int texture[3]);
    float* GetVertices();
    void DrawSkyBox();
};

#pragma once

class Cylinder
{
public:
    unsigned int VBO, VAO, EBO;
    static const int Sides = 360;
    float Radius, Height;
    float CylinderVertices[Sides * 3 * 2];
    unsigned int indices[Sides * 6];

    Cylinder(float radius, float height);
    void DrawCylinder();

private:
    void CreateCylinder();
};


#pragma once

class Cylinder
{
public:
    unsigned int VBO, VAO, EBO;
    static const int Sides = 360;
    float Radius, Height;
    float CylinderVertices[Sides * 8 * 2];
    unsigned int indices[Sides * 6];
    unsigned int textureCylinder;

    Cylinder(float radius, float height, unsigned int texture);
    void DrawCylinder();

private:
    void CreateCylinder();
};


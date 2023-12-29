#include "Classes/Cylinder.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <corecrt_math_defines.h>
#include <vector>
#include <iostream>


Cylinder::Cylinder(float radius, float height) {
    Radius = radius;
    Height = height;
    CreateCylinder();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CylinderVertices), CylinderVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Cylinder::DrawCylinder() {
    glBindVertexArray(VAO);
    // Draw the cylinder using indexed rendering
    glDrawElements(GL_TRIANGLES, 360 * 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Cylinder::CreateCylinder() {
    for (int i = 0; i < Sides; ++i) {
        float angle = glm::radians(static_cast<float>(i));

        // Top circle
        CylinderVertices[i * 3] = Radius * cos(angle);
        CylinderVertices[i * 3 + 1] = Height / 2.0f;
        CylinderVertices[i * 3 + 2] = Radius * sin(angle);

        // Bottom circle
        CylinderVertices[(Sides + i) * 3] = Radius * cos(angle);
        CylinderVertices[(Sides + i) * 3 + 1] = -Height / 2.0f;
        CylinderVertices[(Sides + i) * 3 + 2] = Radius * sin(angle);

        // Indices for indexed rendering
        indices[i * 6] = i;
        indices[i * 6 + 1] = (i + 1) % Sides;
        indices[i * 6 + 2] = Sides + i;

        indices[i * 6 + 3] = Sides + i;
        indices[i * 6 + 4] = (i + 1) % Sides + Sides;
        indices[i * 6 + 5] = (i + 1) % Sides;
    }
}

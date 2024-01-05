#include "Classes/Cylinder.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <corecrt_math_defines.h>
#include <vector>
#include <iostream>

Cylinder::Cylinder(float radius, float height, unsigned int texture) {
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

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normals attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    textureCylinder = texture;
}

void Cylinder::DrawCylinder() {
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureCylinder);
    glDrawElements(GL_TRIANGLES, 360 * 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Cylinder::CreateCylinder() {
    for (int i = 0; i < Sides; ++i) {
        float angle = glm::radians(static_cast<float>(i));

        // Top circle
        // positions
        CylinderVertices[i * 8] = Radius * cos(angle);
        CylinderVertices[i * 8 + 1] = Height / 2.0f;
        CylinderVertices[i * 8 + 2] = Radius * sin(angle);
        // normals
        CylinderVertices[i * 8 + 3] = 0.0f;
        CylinderVertices[i * 8 + 4] = 1.0f;
        CylinderVertices[i * 8 + 5] = 0.0f;
        // texture coords
        CylinderVertices[i * 8 + 6] = static_cast<float>(i) / (Sides - 1); // Texture coordinate U
        CylinderVertices[i * 8 + 7] = 1.0f; // Texture coordinate V

        // Bottom circle
        // positions
        CylinderVertices[(Sides + i) * 8] = Radius * cos(angle);
        CylinderVertices[(Sides + i) * 8 + 1] = -Height / 2.0f;
        CylinderVertices[(Sides + i) * 8 + 2] = Radius * sin(angle);
        // normals
        CylinderVertices[(Sides + i) * 8 + 3] = 0.0f;
        CylinderVertices[(Sides + i) * 8 + 4] = 1.0f;
        CylinderVertices[(Sides + i) * 8 + 5] = 0.0f;
        // texture coords
        CylinderVertices[(Sides + i) * 8 + 6] = static_cast<float>(i) / (Sides - 1); // Texture coordinate U
        CylinderVertices[(Sides + i) * 8 + 7] = 0.0f; // Texture coordinate V

        // Indices for indexed rendering
        indices[i * 6] = i;
        indices[i * 6 + 1] = (i + 1) % Sides;
        indices[i * 6 + 2] = Sides + i;

        indices[i * 6 + 3] = Sides + i;
        indices[i * 6 + 4] = (i + 1) % Sides + Sides;
        indices[i * 6 + 5] = (i + 1) % Sides;
    }
}

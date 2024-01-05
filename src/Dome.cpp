#include "Classes/Dome.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <corecrt_math_defines.h>
#include <vector>
#include <iostream>

Dome::Dome(float radius, int numSegments, unsigned int texture) {
    DomeRadius = radius;
    NumSegments = numSegments;
    DomeVertices = CreateDome();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, DomeVertices.size() * sizeof(glm::vec3), DomeVertices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
    // normals attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(glm::vec3), (void*)sizeof(glm::vec3));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(glm::vec3), (void*)(2 * sizeof(glm::vec3)));
    glEnableVertexAttribArray(2);

    // reuturn to default Bufferss
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    textureDome = texture;
}

void Dome::DrawDome() {
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureDome);
    glDrawArrays(GL_TRIANGLE_FAN, 0, DomeVertices.size());
    glBindVertexArray(0);
}

// Function to create a dome geometry
std::vector<glm::vec3> Dome::CreateDome() {
    std::vector<glm::vec3> vertices;

    for (int i = 0; i <= NumSegments / 1.5; ++i) {
        for (int j = 0; j <= NumSegments; ++j) {
            float phi = glm::pi<float>() * static_cast<float>(i) / (NumSegments) / 1.5;
            float theta = 2.0f * glm::pi<float>() * static_cast<float>(j) / NumSegments;

            float x = DomeRadius * std::sin(phi) * std::cos(theta);
            float y = DomeRadius * std::cos(phi);
            float z = DomeRadius * std::sin(phi) * std::sin(theta);

            float u = static_cast<float>(j) / NumSegments;  // Texture coordinate U
            float v = 1.0f - static_cast<float>(i) / (NumSegments / 1.5); // Texture coordinate V

            // positions
            vertices.push_back(glm::vec3(x, y, z));
            // normals
            vertices.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
            // texture coords
            vertices.push_back(glm::vec3(u, v, 0.0f));
        }
    }

    return vertices;
}

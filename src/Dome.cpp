#include "Classes/Dome.h"
#include<glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <corecrt_math_defines.h>
#include <vector>
#include <iostream>

Dome::Dome(float radius, int numSegments,glm::vec3 color) {
    DomeRadius = radius;
    NumSegments = numSegments;
    DomeVertices = CreateDome();
    DomeShader = Shader("res/shaders/domeShader.shader");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, DomeVertices.size() * sizeof(glm::vec3), DomeVertices.data(), GL_STATIC_DRAW);

    // Vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    // reuturn to default Bufferss
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Dome::DrawDome() {
    DomeShader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, DomeVertices.size());
}

unsigned int Dome::getShaderId() {
    return DomeShader.ID;
}
// Function to create a dome geometry
std::vector<glm::vec3> Dome::CreateDome() {
    std::vector<glm::vec3> vertices;

    for (int i = 0; i <= NumSegments / 1.7; ++i) {
        for (int j = 0; j <= NumSegments; ++j) {
            float phi = glm::pi<float>() * static_cast<float>(i) / (NumSegments) / 1.7;
            float theta = 2.0f * glm::pi<float>() * static_cast<float>(j) / NumSegments;

            float x = DomeRadius * std::sin(phi) * std::cos(theta);
            float y = DomeRadius * std::cos(phi);
            float z = DomeRadius * std::sin(phi) * std::sin(theta);

            vertices.push_back(glm::vec3(x, y, z));
        }
    }

    return vertices;
}

#include "Classes/Sun.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <corecrt_math_defines.h>
#include <vector>
#include <iostream>

Sun::Sun(float radius, int numSegments) {
    SunRadius = radius;
    NumSegments = numSegments;
    SunVertices = CreateSun();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, SunVertices.size() * sizeof(glm::vec3), SunVertices.data(), GL_STATIC_DRAW);

    // Vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    // reuturn to default Bufferss
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Sun::DrawSun() {
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, SunVertices.size());
}

// Function to create a dome geometry
std::vector<glm::vec3> Sun::CreateSun() {
    std::vector<glm::vec3> vertices;

    for (int i = 0; i <= NumSegments; ++i) {
        for (int j = 0; j <= NumSegments; ++j) {
            float phi = glm::pi<float>() * static_cast<float>(i) / (NumSegments);
            float theta = 2.0f * glm::pi<float>() * static_cast<float>(j) / NumSegments;
            float x = SunRadius * std::sin(phi) * std::cos(theta);
            float y = SunRadius * std::cos(phi);
            float z = SunRadius * std::sin(phi) * std::sin(theta);

            vertices.push_back(glm::vec3(x, y, z));
        }
    }

    return vertices;
}

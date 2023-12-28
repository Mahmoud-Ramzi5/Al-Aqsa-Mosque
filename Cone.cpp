#include "Cone.h"
#include<glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <corecrt_math_defines.h>
#include <vector>
#include <iostream>

Cone::Cone(float radius, int numSegments, glm::vec3 color) {
    ConeRadius = radius;
    NumSegments = numSegments;
    ConeVertices = generateConeVertices(ConeRadius,1.0f,4);
    ConeShader = Shader("res/shaders/domeShader.shader");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, ConeVertices.size() * sizeof(glm::vec3), ConeVertices.data(), GL_STATIC_DRAW);

    // Vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    // reuturn to default Bufferss
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Cone::DrawCone() {
    ConeShader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, ConeVertices.size());
}

unsigned int Cone::getShaderId() {
    return ConeShader.ID;
}
// Function to create a dome geometry
std::vector<glm::vec3> generateConeVertices(float radius, float height, int sides) {
    std::vector<glm::vec3> vertices;

    // Vertex at the tip of the cone
    vertices.push_back(glm::vec3(0.0f, 0.0f, height));

    // Vertices for the circular base
    for (int i = 0; i < sides; ++i) {
        float angle = 2.0f * M_PI * i / sides;
        float x = radius * std::cos(angle);
        float y = radius * std::sin(angle);
        float z = 0.0f;
        vertices.push_back(glm::vec3(x, y, z));
    }

    return vertices;
}

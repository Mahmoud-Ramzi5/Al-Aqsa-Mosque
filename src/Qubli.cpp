#include "Classes/Qubli.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Qubli::Qubli(unsigned int texture) {

    vertice[0].positions = glm::vec3(-0.5f, 0.0f, -0.7f);
    vertice[0].texture = glm::vec2(0.0f, 0.0f);

    vertice[1].positions = glm::vec3(0.5f, 0.0f, -0.7f);
    vertice[1].texture = glm::vec2(0.304f, 0.0f);

    vertice[2].positions = glm::vec3(0.5f, 0.0f, 0.7f);
    vertice[2].texture = glm::vec2(0.592f, 0.0f);

    vertice[3].positions = glm::vec3(-0.5f, 0.0f, 0.7f);
    vertice[3].texture = glm::vec2(0.712f, 0.0f);

    vertice[4].positions = glm::vec3(-0.5f, 0.2f, -0.7f);
    vertice[4].texture = glm::vec2(0.0f, 0.0f);

    vertice[5].positions = glm::vec3(0.5f, 0.2f, -0.7f);
    vertice[5].texture = glm::vec2(0.304f, 0.0f);

    vertice[6].positions = glm::vec3(0.5f, 0.2f, 0.7f);
    vertice[6].texture = glm::vec2(0.592f, 0.0f);

    vertice[7].positions = glm::vec3(-0.5f, 0.2f, 0.7f);
    vertice[7].texture = glm::vec2(0.712f, 0.0f);

    vertice[8].positions = glm::vec3(-0.5f, 0.0f, -0.7f);
    vertice[8].texture = glm::vec2(1.0f, 0.0f);

    vertice[9].positions = glm::vec3(-0.5f, 0.2f, -0.7f);
    vertice[9].texture = glm::vec2(1.0f, 1.0f);


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // reuturn to default Bufferss
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    textureQubli = texture;
}

float* Qubli::GetVertices() {
    return vertices;
}

unsigned int* Qubli::GetIndices() {
    return indices;
}

void Qubli::DrawQubli()
{
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, textureQubli);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

glm::vec3 calculateFaceNormal(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2) {
    glm::vec3 edge1 = v1 - v0;
    glm::vec3 edge2 = v2 - v0;
    return glm::normalize(glm::cross(edge1, edge2));
}

#include "Wall.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <corecrt_math_defines.h>
#include <vector>
#include <iostream>
#include <shader.h>

Wall::Wall(unsigned int texture) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // reuturn to default Bufferss
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    textureWall = texture;
    
}

void Wall::DrawWall(unsigned int shaderId, int i) {
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, textureWall);
    /*if (i == 2 || i == 3) {
        glm::mat4 model = glm::mat4(1.0f);  // Initialize matrix to identity matrix first
        model = glm::translate(model, WallPositions[i]);

        // Rotate the cube
        float rotationAngle = 90.0f;  // Rotation angle in degrees
        glm::vec3 rotationAxis(0.0f, 1.0f, 0.0f);  // Rotation axis
        model = glm::rotate(model, glm::radians(rotationAngle), rotationAxis);
        unsigned int modelLoc = glGetUniformLocation(shaderId, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, 1);
        return;
    }
    // calculate the model matrix for each object and pass it to shader before drawing
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::translate(model, WallPositions[i]);

    unsigned int modelLoc = glGetUniformLocation(shaderId, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    */
    glDrawArrays(GL_TRIANGLES, 0, 36);

}
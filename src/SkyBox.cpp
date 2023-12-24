#include "SkyBox.h"
#include<glad/glad.h>

SkyBox::SkyBox(unsigned int texture[6]) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SkyboxVertices), SkyboxVertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // reuturn to default Bufferss
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    for (int i = 0; i < 6; i++) {
        textureSky[i] = texture[i];
    }
}

float* SkyBox::GetVertices() {
    return SkyboxVertices;
}

void SkyBox::DrawSkyBox() {
    glBindVertexArray(VAO);
    for (int i = 0; i < 6; i++) {
        glBindTexture(GL_TEXTURE_2D, textureSky[i]);
        glDrawArrays(GL_TRIANGLES, (i * 6), 6);
    }
}

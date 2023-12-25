#ifndef PLAYER_H
#define PLAYER_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <model.h>

class Player
{
public:
	glm::vec3 Position;
	Model Pmodel;

	Player() {}

	Player(glm::vec3 position, std::string player) {
		Position = position;
		Pmodel = Model(player);
	}

	void DrawPlayer(Shader shader, glm::vec3 pos) {
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		model = glm::mat4(1.0f);
		
		model = glm::translate(model, pos);
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
		unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pmodel.Draw(shader);
	}
};
#endif
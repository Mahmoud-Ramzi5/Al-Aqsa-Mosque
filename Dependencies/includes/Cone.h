#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <corecrt_math_defines.h>
#include <vector>
#include <iostream>
#include<shader.h>

class Cone
{
public:
	unsigned int VBO, VAO;
	float ConeRadius;
	int NumSegments;
	std::vector<glm::vec3> ConeVertices;
	Shader ConeShader;
	glm::vec3 color;

	Cone(float radius, int numSegments, glm::vec3 color);
	void DrawCone();
	unsigned int getShaderId();

private:
	std::vector<glm::vec3> generateConeVertices(float radius, float height, int sides);
};


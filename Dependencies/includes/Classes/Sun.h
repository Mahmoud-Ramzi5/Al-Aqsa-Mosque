#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <corecrt_math_defines.h>
#include <vector>
#include <iostream>
#include <shader.h>

class Sun
{
public:
	unsigned int VBO, VAO;
	float SunRadius;
	int NumSegments;
	std::vector<glm::vec3> SunVertices;

	Sun(float radius, int numSegments);
	void DrawSun();

private:
	std::vector<glm::vec3> CreateSun();
};


#pragma once
#include<glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <corecrt_math_defines.h>
#include <vector>
#include <iostream>

class Dome
{
public:
	unsigned int VBO, VAO;
	float DomeRadius;
	int NumSegments;
	std::vector<glm::vec3> DomeVertices;

	Dome(float radius, int numSegments);
	void DrawDome();

private:
	std::vector<glm::vec3> CreateDome();
};


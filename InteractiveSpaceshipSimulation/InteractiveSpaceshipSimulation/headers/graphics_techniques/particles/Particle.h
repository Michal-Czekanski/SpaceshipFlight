#pragma once

#include "glm.hpp"
#include "ext.hpp"

class Particle
{
public:
	Particle(glm::vec3 position, glm::vec4 color, glm::vec3 velocity);
private:
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 velocity;
	const float maxLife = 1.0f;
	const float minLife = 0.0f;
	float life;

};


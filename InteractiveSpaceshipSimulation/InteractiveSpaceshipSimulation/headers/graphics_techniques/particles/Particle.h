#pragma once

#include "glm.hpp"
#include "ext.hpp"
#include "utils/Time.h"

class Particle
{
public:
	Particle();
	Particle(glm::vec3 position, glm::vec4 color, glm::vec3 velocity);
	Particle(const Particle& p);
	Particle operator= (const Particle& p);
	bool isAlive();
	void update();

	glm::vec3 getPosition();
	glm::vec4 getColor();
	glm::vec3 getVelocity();
	float getLife();
private:
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 velocity;
	const float maxLife = 1.0f;
	const float minLife = 0.0f;
	float life;
};


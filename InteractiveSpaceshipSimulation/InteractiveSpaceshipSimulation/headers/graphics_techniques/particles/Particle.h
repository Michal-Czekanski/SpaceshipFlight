#pragma once

#include "glm.hpp"
#include "ext.hpp"
#include "utils/Time.h"

class Particle
{
public:
	Particle();
	Particle(glm::vec3 position, glm::vec4 color, glm::vec3 velocity, glm::vec3 cameraPos, float size = 1.0f);
	Particle(const Particle& p);
	Particle operator= (const Particle& p);
	bool operator < (const Particle& other) const;
	bool isAlive();
	void update(glm::vec3 cameraPos);

	glm::vec3 getPosition();
	glm::vec4 getColor();
	glm::vec3 getVelocity();
	float getLife();
	float getSize();
	float getDistanceFromCamera();
private:
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 velocity;
	const float maxLife = 1.0f;
	const float minLife = 0.0f;
	float life;
	float size;
	float distFromCamera;
};


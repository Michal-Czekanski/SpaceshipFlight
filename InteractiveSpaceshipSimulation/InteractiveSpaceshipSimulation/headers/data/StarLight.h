#pragma once

#include "glm.hpp"
#include "ext.hpp"

class StarLight
{
private:
	float strength;
	glm::vec3 color;
	glm::vec3 position;

public:
	StarLight(glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float strenght = 3580000.0f);

	float getStrength();

	glm::vec3 getColor();
	glm::vec3 getPosition();

	void update(glm::vec3 position);

	void setStrength(float strength);
};


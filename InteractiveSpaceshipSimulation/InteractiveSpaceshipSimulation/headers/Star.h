#pragma once

#include "RenderableObject.h"

class Star : public RenderableObject
{
private:
	glm::vec3 lightColor;
	float lightStrength;
public:
	Star(glm::vec3 position, ModelData &modelData, glm::vec3 scale,
		glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f), float lightStrength = 5000000.0f);

	glm::vec3 getLightColor();

	float getLightStrength();
};


#pragma once

#include "RenderableObject.h"

class Star : public RenderableObject
{
private:
	StarLight light;

public:
	Star(glm::vec3 position, ModelData &modelData, glm::vec3 scale, StarLight *light);

	StarLight getLight();
};


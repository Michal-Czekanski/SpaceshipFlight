#pragma once
#include "RenderableObject.h"

class Asteroid: public RenderableObject
{
private:
	float speed;
	glm::vec3 moveDirection;

public:
	Asteroid(ModelData &modelData, glm::vec3 position, glm::vec3 moveDirection, float speed, 
		glm::vec3 scale);

	void update();
};


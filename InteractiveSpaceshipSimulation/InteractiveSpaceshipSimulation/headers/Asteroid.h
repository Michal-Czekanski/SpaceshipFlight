#pragma once
#include "RenderableObject.h"

class Asteroid: public RenderableObject
{
private:
	float speed;
	glm::vec3 moveDirection;

public:
	Asteroid(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop, obj::Model model, glm::vec3 topInModelSpace, glm::vec3 forwardInModelSpace,
		glm::vec3 scale, float speed, glm::vec3 moveDirection);

	void update();
};


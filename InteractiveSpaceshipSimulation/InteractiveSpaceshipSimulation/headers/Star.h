#pragma once

#include "RenderableObject.h"

class Star : public RenderableObject
{
public:
	Star(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward,
		glm::vec3 vectorTop, obj::Model model, glm::vec3 topInModelSpace, glm::vec3 forwardInModelSpace, glm::vec3 scale);
};


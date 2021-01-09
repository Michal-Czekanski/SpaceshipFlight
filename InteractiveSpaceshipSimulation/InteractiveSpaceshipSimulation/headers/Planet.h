#pragma once

#include "RenderableObject.h"
#include "Star.h"

class Planet: public RenderableObject
{
private:
	/// <summary>
	/// Star around which this planet orbits.
	/// </summary>
	Star* orbitAround = NULL;

public:
	/// <summary>
	/// Creates Planet which will not orbit around any star.
	/// </summary>
	Planet(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop, obj::Model model, glm::vec3 topInModelSpace, glm::vec3 forwardInModelSpace,
		glm::vec3 scale);
};


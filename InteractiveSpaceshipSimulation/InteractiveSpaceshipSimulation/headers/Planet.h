#pragma once

#include "RenderableObject.h"
#include "Star.h"
#include "utils/Calculations.h"
#include "Orbitable.h"

class Planet: public Orbitable
{
public:
	/// <summary>
	/// Creates Planet which will not orbit around any star.
	/// </summary>
	Planet(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop, obj::Model model, glm::vec3 topInModelSpace, glm::vec3 forwardInModelSpace,
		glm::vec3 scale);

	/// <summary>
	/// Creates Planet which orbits around given Star.
	/// </summary>
	/// <param name="orbitAround">Star to orbit around.</param>
	/// <param name="orbitPlaneVec2">Second of the two vectors defining rotation plane. First one is calculated as vector pointing from Sun to Planet.</param>
	Planet(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop, obj::Model model, glm::vec3 topInModelSpace, glm::vec3 forwardInModelSpace,
		glm::vec3 scale, Star* orbitAround, glm::vec3 orbitPlaneVec2, float orbitSpeed);

	void update();
};


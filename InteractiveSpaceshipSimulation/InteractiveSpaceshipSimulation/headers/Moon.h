#pragma once

#include "Orbitable.h"
#include "Planet.h"

class Moon: public Orbitable
{
public:
	/// <summary>
	/// Creates Moon which orbits around given Planet.
	/// </summary>
	/// <param name="orbitAround">Planet to orbit around.</param>
	/// <param name="orbitPlaneVec2">Second of the two vectors defining rotation plane. First one is calculated as vector pointing from Planet to Moon.</param>
	Moon(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop, obj::Model model, glm::vec3 topInModelSpace, glm::vec3 forwardInModelSpace,
		glm::vec3 scale, Planet* orbitAround, glm::vec3 orbitPlaneVec2, float orbitSpeed);

	void update();
};


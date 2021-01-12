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
	Moon(glm::vec3 position, ModelData& modelData,
		glm::vec3 scale, Planet* orbitAround, glm::vec3 orbitPlaneVec2, float orbitSpeed);
};


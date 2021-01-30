#pragma once

#include "objectsInSpace/renderables/RenderableObject.h"
#include "objectsInSpace/renderables/Star.h"
#include "utils/Calculations.h"
#include "Orbitable.h"

class Planet: public Orbitable
{
private:
	Star* orbitAround = NULL;
public:
	/// <summary>
	/// Creates Planet which will not orbit around any star.
	/// </summary>
	Planet(glm::vec3 position, ModelData& modelData,
		glm::vec3 scale, GLuint programDraw);

	/// <summary>
	/// Creates Planet which orbits around given Star.
	/// </summary>
	/// <param name="orbitAround">Star to orbit around.</param>
	/// <param name="orbitPlaneVec2">Second of the two vectors defining rotation plane. First one is calculated as vector pointing from Sun to Planet.</param>
	Planet(glm::vec3 position, ModelData& modelData,
		glm::vec3 scale, Star* orbitAround, glm::vec3 orbitPlaneVec2, float orbitSpeed, GLuint programDraw);

	void update();

	Star* getOrbitCenter();
};


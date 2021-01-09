#pragma once

#include "RenderableObject.h"
#include "Star.h"
#include "utils/Calculations.h"

class Planet: public RenderableObject
{
private:
	/// <summary>
	/// Star around which this planet orbits.
	/// </summary>
	Star* orbitAround = NULL;

	/// <summary>
	/// Plane in which planet orbits around Star. First vector defining this plane is direction vector pointing from Star's center to Planet's center.
	/// </summary>
	glm::vec3 orbitPlane[2];

	/// <summary>
	/// Axis along which Planet orbits around Star. It is orthogonal to the orbitPlane.
	/// </summary>
	glm::vec3 orbitAxis;

	/// <summary>
	/// Quat used to rotate planet around star.
	/// </summary>
	glm::quat orbitQuat;

	float orbitSpeed;


	/// <summary>
	/// Position relative to the Star around which Planet orbits.
	/// </summary>
	glm::vec3 posRelativeToStar;

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


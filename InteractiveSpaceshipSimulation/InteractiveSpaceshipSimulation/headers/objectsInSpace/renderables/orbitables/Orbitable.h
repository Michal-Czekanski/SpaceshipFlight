#pragma once

#include "../RenderableObject.h"
#include "../../../utils/Calculations.h"

class Orbitable: public RenderableObject
{
protected:
	/// <summary>
	/// Object around which this orbits.
	/// </summary>
	ObjectInSpace* orbitAround = NULL;

	/// <summary>
	/// Plane in which this object orbits. First vector defining this plane is direction vector pointing from orbitAround object's center to this object's center.
	/// </summary>
	glm::vec3 orbitPlane[2];

	/// <summary>
	/// Axis along which this object orbits around orbitAround object. It is orthogonal to the orbitPlane.
	/// </summary>
	glm::vec3 orbitAxis;

	/// <summary>
	/// Quat used to rotate this object around orbitAround object.
	/// </summary>
	glm::quat orbitQuat;

	float orbitSpeed;
	
	/// <summary>
	/// Vector pointing from orbit center to this object's initial position in world.
	/// </summary>
	glm::vec3 initPosRelativeToOrbitCenter;
	/// <summary>
	/// Vector pointing from orbit center to this object.
	/// </summary>
	glm::vec3 posRelativeToOrbitCenter;

public:
	/// <summary>
	/// Creates object which orbits around other object.
	/// </summary>
	/// <param name="orbitAround">Object to orbit around.</param>
	/// <param name="orbitPlaneVec2">Second of the two vectors defining rotation plane. First one is calculated as vector pointing from orbitAround object to this object.</param>
	Orbitable(glm::vec3 position, ModelData& modelData, glm::vec3 scale,
		ObjectInSpace* orbitAround, glm::vec3 orbitPlaneVec2, float orbitSpeed, GLuint programDraw);

	/// <summary>
	/// Makes object orbit -> updates it's position based on orbitSpeed.
	/// </summary>
	void orbit();

	/// <summary>
	/// Returns position of object around which this object orbits.
	/// </summary>
	/// <returns></returns>
	glm::vec3 getOrbitCenterPos();

	/// <summary>
	/// Returns object around which this object orbits.
	/// </summary>
	/// <returns></returns>
	ObjectInSpace* getOrbitCenter();

	void update();
};


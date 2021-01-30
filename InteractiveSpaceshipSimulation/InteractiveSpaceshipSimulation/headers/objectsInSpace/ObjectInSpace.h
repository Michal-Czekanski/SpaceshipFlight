#pragma once

#include "glm.hpp"
#include "ext.hpp"

/// <summary>
/// Object in space with position and direction.
/// </summary>
class ObjectInSpace
{
protected:
	glm::vec3 position;
	
	glm::vec3 vectorForward;
	glm::vec3 initialVectorForward;


	glm::vec3 vectorTop;
	glm::vec3 initialVectorTop;


	glm::vec3 vectorRight;

	glm::quat rotationQuat;

	/// <summary>
	/// Updates direction vectors after rotation.
	/// </summary>
	/// <param name="rotation">Rotation quaternion which affects directions.</param>
	void updateDirections(glm::quat rotation);
public:
	ObjectInSpace(glm::vec3 position, glm::vec3 vectorForward, glm::vec3 vectorTop);

	glm::vec3 getPosition();
	glm::vec3 getVectorForward();
	glm::vec3 getVectorTop();
	void setPosition(glm::vec3 newPosition);

	virtual void rotate(glm::quat rotation);

	glm::quat getRotationQuat();

};


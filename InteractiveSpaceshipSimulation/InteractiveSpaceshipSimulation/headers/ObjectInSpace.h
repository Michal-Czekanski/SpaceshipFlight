#pragma once

#include "glm.hpp"
#include "ext.hpp"

class ObjectInSpace
{
protected:
	glm::vec3 position;
	glm::quat rotationQuat;
	glm::mat4 rotationMat;

	glm::vec3 vectorForward;
	glm::vec3 vectorTop;
	glm::vec3 vectorRight;
public:
	ObjectInSpace(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop);

	glm::vec3 getPosition();
	glm::quat getRotationQuat();
	glm::vec3 getVectorForward();
	glm::vec3 getVectorTop();

	void setPosition(glm::vec3 newPosition);
	void setRottaionQuat(glm::quat newRotation);

};


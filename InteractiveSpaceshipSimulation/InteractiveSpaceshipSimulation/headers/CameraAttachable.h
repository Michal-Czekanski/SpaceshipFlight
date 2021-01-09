#pragma once

#include "glm.hpp"
#include "ext.hpp"

class CameraAttachable
{
protected:
	glm::vec3 position;
	glm::quat rotationQuat;

	glm::vec3 vectorForward;
	glm::vec3 vectorTop;
public:
	CameraAttachable(glm::vec3 position, glm::quat rotationQuat, glm::vec3 vectorForward, glm::vec3 vectorTop);

	glm::vec3 getPosition();
	glm::quat getRotationQuat();
	glm::vec3 getVectorForward();
	glm::vec3 getVectorTop();
};


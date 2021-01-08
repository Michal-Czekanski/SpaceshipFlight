#pragma once

#include "glm.hpp"
#include "ext.hpp"

class ICameraAttachable
{
protected:
	glm::vec3 position;
	glm::quat rotationQuat;

	glm::vec3 vectorForward;
	glm::vec3 vectorTop;
public:
	virtual glm::vec3 getPosition();
	virtual glm::quat getRotationQuat();
	virtual glm::vec3 getVectorForward();
	virtual glm::vec3 getVectorTop();
};


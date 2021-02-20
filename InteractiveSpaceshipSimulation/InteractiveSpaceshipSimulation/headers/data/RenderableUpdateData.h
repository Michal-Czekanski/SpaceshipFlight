#pragma once

#include "utils/PhysxGLMConverter.h"

class RenderableUpdateData
{
public:
	RenderableUpdateData(PxTransform data);
	glm::quat& getRotation();
	glm::vec3& getPosition();
	glm::mat4& getModelMatrix();
private:
	glm::quat rotation;
	glm::vec3 position;
	glm::mat4 modelMatrix;
};


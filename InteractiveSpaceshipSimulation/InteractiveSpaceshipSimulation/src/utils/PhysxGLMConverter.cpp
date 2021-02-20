#include "utils/PhysxGLMConverter.h"

glm::vec3 PhysxGLMConverter::PxVec3ToVec3(PxVec3 pxVec3)
{
	return glm::vec3(pxVec3.x, pxVec3.y, pxVec3.z);
}

PxVec3 PhysxGLMConverter::vec3ToPxVec3(glm::vec3 vec3)
{
	return PxVec3(vec3.x, vec3.y, vec3.z);
}

PxVec2 PhysxGLMConverter::vec2ToPxVec2(glm::vec2 vec2)
{
	return PxVec2(vec2.x, vec2.y);
}

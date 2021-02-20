#include "utils/PhysxGLMConverter.h"

glm::vec3 PhysxGLMConverter::PxVec3ToVec3(PxVec3 pxVec3)
{
	return glm::vec3(pxVec3.x, pxVec3.y, pxVec3.z);
}

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

glm::quat PhysxGLMConverter::PxQuatToQuat(PxQuat pxQ)
{
	return glm::quat(pxQ.w, pxQ.x, pxQ.y, pxQ.z);
}

PxQuat PhysxGLMConverter::quatToPxQuat(glm::quat q)
{
    return PxQuat(q.x, q.y, q.z, q.w);
}

glm::mat4 PhysxGLMConverter::PxMat44ToMat4(PxMat44 pxM)
{
    auto& c0 = pxM.column0;
    auto& c1 = pxM.column1;
    auto& c2 = pxM.column2;
    auto& c3 = pxM.column3;

    glm::mat4 result(
        c0.x, c0.y, c0.z, c0.w,
        c1.x, c1.y, c1.z, c1.w,
        c2.x, c2.y, c2.z, c2.w,
        c3.x, c3.y, c3.z, c3.w);
    return result;
}

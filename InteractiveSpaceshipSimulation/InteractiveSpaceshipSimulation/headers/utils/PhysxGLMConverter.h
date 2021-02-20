#pragma once

#include "glm.hpp"
#include "ext.hpp"
#include "PxPhysicsAPI.h"

using namespace physx;

/// <summary>
/// Static class capable of converting values from glm to physx and in reverse.
/// </summary>
class PhysxGLMConverter
{
public:
	static glm::vec3 PxVec3ToVec3(PxVec3 pxVec3);
	static PxVec3 vec3ToPxVec3(glm::vec3 vec3);
	static PxVec2 vec2ToPxVec2(glm::vec2 vec2);
	static glm::quat PxQuatToQuat(PxQuat pxQ);
	static glm::mat4 PxMat44ToMat4(PxMat44 pxM);
};


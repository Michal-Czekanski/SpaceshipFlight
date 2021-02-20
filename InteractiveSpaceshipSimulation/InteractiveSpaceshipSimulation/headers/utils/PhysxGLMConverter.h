#pragma once

#include "glm.hpp"
#include "ext.hpp"
#include "PxPhysicsAPI.h"

using namespace physx;

class PhysxGLMConverter
{
public:
	static glm::vec3 PxVec3ToVec3(PxVec3 pxVec3);
};


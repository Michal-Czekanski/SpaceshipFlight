#pragma once

#include "PxPhysicsAPI.h"

using namespace physx;

class IDynamicRigidbody
{
public:
	virtual void addForce(PxVec3 force, PxForceMode::Enum mode=PxForceMode::eFORCE, bool autowake=true) = 0;
};


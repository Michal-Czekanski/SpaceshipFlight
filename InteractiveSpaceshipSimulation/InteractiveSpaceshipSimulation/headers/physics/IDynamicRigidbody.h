#pragma once

#include "PxPhysicsAPI.h"

using namespace physx;

class IDynamicRigidbody
{
public:
	virtual PxRigidDynamic* getRigidDynamic() = 0;
};


#pragma once

#include "PxPhysicsAPI.h"

class PhysicsOptions
{
public:
	const float getGravity();
	const float getStepTime();
	physx::PxSceneDesc& getSceneDesc();

private:
	const float gravity = 0.0f;
	const float stepTime = 1 / 60.0f;
	physx::PxSceneDesc scnDesc;
};


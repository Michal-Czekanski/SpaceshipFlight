#pragma once

#include "PxPhysicsAPI.h"
#include "physics/data/SimulationEventCallback.h"
#include "physics/data/simulationFilterShader.h"

class PhysicsOptions
{
public:
	PhysicsOptions();
	const float getGravity();
	const float getStepTime();
	physx::PxSceneDesc& getSceneDesc();

private:
	const float gravity = 0.0f;
	const float stepTime = 1 / 60.0f;
	physx::PxSceneDesc scnDesc;
};


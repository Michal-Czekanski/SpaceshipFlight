#pragma once

#include "PxPhysicsAPI.h"

using namespace physx;

class Physics
{
public:
private:
	static Physics instance;
	const float stepTime;
	float timeToProcess = 0.0f;
	const float maxDeltaTime = 1.0f;
	PxPhysics* pxPhysics;
	PxScene* pxScene;
};


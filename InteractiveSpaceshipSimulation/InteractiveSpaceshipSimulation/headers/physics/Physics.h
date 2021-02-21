#pragma once

#include "data/PhysicsOptions.h"

class Physics
{
public:
	Physics* getInstance();
	PxPhysics* getPxPhysics();
	PxScene* getPxScene();
private:
	static Physics* instance;
	Physics(PhysicsOptions& options);
	const float stepTime;
	float timeToProcess = 0.0f;
	const float maxDeltaTime = 1.0f;
	PxPhysics* pxPhysics;
	PxScene* pxScene;

	PxDefaultAllocator		allocator;
	PxDefaultErrorCallback	errorCallback;
	PxFoundation* foundation = nullptr;
	PxDefaultCpuDispatcher* dispatcher = nullptr;
};


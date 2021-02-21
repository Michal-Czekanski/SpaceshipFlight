#pragma once

#include "data/PhysicsOptions.h"

class Physics
{
public:
	Physics* getInstance();
	PxPhysics* getPxPhysics();
	PxScene* getPxScene();

	/// <summary>
	/// Updates physics simulation.
	/// </summary>
	/// <param name="deltaTime">How much time passed since last update.</param>
	void update(float deltaTime);

private:
	static Physics* instance;
	Physics(PhysicsOptions& options);
	const float stepTime;
	float timeToProcess = 0.0f;
	const float maxDeltaTime = 1.0f;
	PxPhysics* pxPhysics;
	PxScene* pxScene;

	/// <summary>
	/// Updates pxScene.
	/// </summary>
	/// <param name="stepTime"></param>
	void updateStep(float stepTime);

	PxDefaultAllocator		allocator;
	PxDefaultErrorCallback	errorCallback;
	PxFoundation* foundation = nullptr;
	PxDefaultCpuDispatcher* dispatcher = nullptr;
};


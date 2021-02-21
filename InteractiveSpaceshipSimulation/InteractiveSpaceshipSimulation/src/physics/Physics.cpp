#include "physics/Physics.h"

Physics* Physics::instance = nullptr;

Physics* Physics::getInstance()
{
	if (!instance) 
	{
		PhysicsOptions options = PhysicsOptions();
		instance = new Physics(options);
	}
	return instance;
}

PxPhysics* Physics::getPxPhysics()
{
	return pxPhysics;
}

PxScene* Physics::getPxScene()
{
	return pxScene;
}

void Physics::update(float deltaTime)
{
	if (deltaTime <= maxDeltaTime)
	{
		timeToProcess += deltaTime;
		while (timeToProcess > 0)
		{
			updateStep(stepTime);
			timeToProcess -= stepTime;
		}
	}
}

Physics::Physics(PhysicsOptions& options): stepTime(options.getStepTime())
{
	foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocator, errorCallback);

	pxPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, options.getSceneDesc().getTolerancesScale(), true);
	
	dispatcher = PxDefaultCpuDispatcherCreate(2);
	
	options.getSceneDesc().cpuDispatcher = dispatcher;
	pxScene = pxPhysics->createScene(options.getSceneDesc());
}

void Physics::updateStep(float stepTime)
{
	pxScene->simulate(stepTime);
	pxScene->fetchResults(true);
}

#include "physics/Physics.h"

Physics* Physics::instance = nullptr;

Physics* Physics::getInstance()
{
	if (!instance) 
	{
		PhysicsOptions options;
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

Physics::Physics(PhysicsOptions& options): stepTime(options.getStepTime())
{
	dispatcher = (PxDefaultCpuDispatcher*)options.getSceneDesc().cpuDispatcher;
	foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocator, errorCallback);
	pxPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, options.getSceneDesc().getTolerancesScale(), true);
	pxScene = pxPhysics->createScene(options.getSceneDesc());
}

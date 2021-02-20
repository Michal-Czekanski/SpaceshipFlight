#include "physics/PhysicsOptions.h"



const float PhysicsOptions::getGravity()
{
	return gravity;
}

const float PhysicsOptions::getStepTime()
{
	return stepTime;
}

physx::PxSceneDesc& PhysicsOptions::getSceneDesc()
{
	return scnDesc;
}

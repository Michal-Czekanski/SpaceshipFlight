#include "physics/Physics.h"

PxPhysics* Physics::getPxPhysics()
{
	return pxPhysics;
}

PxScene* Physics::getPxScene()
{
	return pxScene;
}

#include "physics/data/PhysicsOptions.h"



PhysicsOptions::PhysicsOptions(): scnDesc(PxTolerancesScale())
{
	scnDesc.gravity = PxVec3(0.0f, -gravity, 0.0f);
    
    scnDesc.filterShader = simulationFilterShader;
    scnDesc.kineKineFilteringMode = PxPairFilteringMode::eKEEP; // So kin-kin contacts with be reported
    scnDesc.staticKineFilteringMode = PxPairFilteringMode::eKEEP; // So static-kin constacts will be reported
    scnDesc.simulationEventCallback = new SimulationEventCallback();
}

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

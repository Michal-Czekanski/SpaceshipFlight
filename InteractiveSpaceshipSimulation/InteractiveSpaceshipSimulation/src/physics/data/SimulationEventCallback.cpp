#include "physics/data/SimulationEventCallback.h"

void SimulationEventCallback::onConstraintBreak(PxConstraintInfo* constraints, PxU32 count)
{
}

void SimulationEventCallback::onWake(PxActor** actors, PxU32 count)
{
}

void SimulationEventCallback::onSleep(PxActor** actors, PxU32 count)
{
}

void SimulationEventCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{
}

void SimulationEventCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
}

void SimulationEventCallback::onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count)
{
}

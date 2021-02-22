#include "physics/data/SimulationEventCallback.h"
#include "objectsInSpace/renderables/Ship.h"

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
	// Detect only Ship collisions
	if (!(pairHeader.actors[0]->userData == ShipPointer::shipPointer ||
		pairHeader.actors[1]->userData == ShipPointer::shipPointer))
		return;

	((Ship*)ShipPointer::shipPointer)->hit();
}

void SimulationEventCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
}

void SimulationEventCallback::onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count)
{
}

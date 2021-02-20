#pragma once

#include "PxPhysicsAPI.h"

using namespace physx;

inline static PxFilterFlags simulationFilterShader(PxFilterObjectAttributes attributes0,
    PxFilterData filterData0, PxFilterObjectAttributes attributes1, PxFilterData filterData1,
    PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
    pairFlags =
        PxPairFlag::eCONTACT_DEFAULT | // default contact processing
        PxPairFlag::eNOTIFY_CONTACT_POINTS | // contact points will be available in onContact callback
        PxPairFlag::eNOTIFY_TOUCH_FOUND; // onContact callback will be called for this pair

    return physx::PxFilterFlag::eDEFAULT;
}
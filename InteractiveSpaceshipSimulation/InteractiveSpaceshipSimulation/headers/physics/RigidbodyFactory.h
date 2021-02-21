#pragma once

#include "utils/PhysxGLMConverter.h"
#include "physics/Physics.h"

class RigidbodyFactory
{
public:
	static PxRigidDynamic* createShipRigidbody(glm::vec3 position, glm::quat rotation, void* shipPointer);
};


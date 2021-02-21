#pragma once

#include "utils/PhysxGLMConverter.h"
#include "physics/Physics.h"

class RigidbodyFactory
{
public:
	static PxRigidDynamic* createShipRigidbody(glm::vec3 position, glm::quat rotation, void* shipPointer);
	static PxRigidDynamic* createAsteroidRigidbody(glm::vec3 position, glm::quat rotation, void* asteroidPointer);

private:
	static PxRigidDynamic* createDynamicRigidbody(glm::vec3 position, glm::quat rotation, void* userData, 
		PxMaterial* mat, PxGeometry& geometry);
};


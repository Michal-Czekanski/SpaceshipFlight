#pragma once

#include "utils/PhysxGLMConverter.h"
#include "physics/Physics.h"
#include "objectsInSpace/renderables/RenderableObject.h"

class RigidbodyFactory
{
public:
	static PxRigidDynamic* createShipRigidbody(glm::vec3 position, glm::quat rotation, void* shipPointer);
	static PxRigidDynamic* createAsteroidRigidbody(glm::vec3 position, glm::quat rotation, void* asteroidPointer);
	/// <summary>
	/// Creates rigidbody for planet, moon, or star.
	/// </summary>
	static PxRigidDynamic* createPlanetMoonStarRigidbody(glm::vec3 position, glm::quat rotation, void* objectPointer);

private:
	static PxRigidDynamic* createDynamicRigidbody(glm::vec3 position, glm::quat rotation, void* userData, 
		PxMaterial* mat, PxGeometry& geometry);
	static PxRigidDynamic* createKinematicRigidbody(glm::vec3 position, glm::quat rotation, void* userData,
		PxMaterial* mat, PxGeometry& geometry);
};


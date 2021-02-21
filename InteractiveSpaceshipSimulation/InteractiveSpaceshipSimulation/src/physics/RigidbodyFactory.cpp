#include "physics/RigidbodyFactory.h"

PxRigidDynamic* RigidbodyFactory::createShipRigidbody(glm::vec3 position, glm::quat rotation, void* shipPointer)
{
	PxMaterial* material = Physics::getInstance()->getPxPhysics()->createMaterial(0.5, 0.5, 0.6);
	PxGeometry geometry = PxBoxGeometry(1, 1, 1); // TODO
	return createDynamicRigidbody(position, rotation, shipPointer, material, geometry);
}

PxRigidDynamic* RigidbodyFactory::createAsteroidRigidbody(glm::vec3 position, glm::quat rotation, void* asteroidPointer)
{
	PxMaterial* material = Physics::getInstance()->getPxPhysics()->createMaterial(0.5, 0.5, 0.6);
	PxGeometry geometry = PxSphereGeometry(1); // TODO
	return createDynamicRigidbody(position, rotation, asteroidPointer, material, geometry);
}

PxRigidDynamic* RigidbodyFactory::createPlanetMoonStarRigidbody(glm::vec3 position, glm::quat rotation, void* planetPointer)
{
	PxMaterial* material = Physics::getInstance()->getPxPhysics()->createMaterial(0.5, 0.5, 0.6);
	PxGeometry geometry = PxSphereGeometry(1); // TODO
	return createKinematicRigidbody(position, rotation, planetPointer, material, geometry);
}

PxRigidDynamic* RigidbodyFactory::createDynamicRigidbody(glm::vec3 position, glm::quat rotation, void* userData, PxMaterial* mat, PxGeometry& geometry)
{
	PxPhysics* pxPhysics = Physics::getInstance()->getPxPhysics();
	PxScene* pxScene = Physics::getInstance()->getPxScene();

	PxRigidDynamic* body = pxPhysics->createRigidDynamic(
		PxTransform(PhysxGLMConverter::vec3ToPxVec3(position), PhysxGLMConverter::quatToPxQuat(rotation)));

	PxShape* shape = pxPhysics->createShape(geometry, *mat);
	body->attachShape(*shape);
	shape->release();
	body->userData = userData;
	pxScene->addActor(*body);
	return body;
}

PxRigidDynamic* RigidbodyFactory::createKinematicRigidbody(glm::vec3 position, glm::quat rotation, void* userData, PxMaterial* mat, PxGeometry& geometry)
{
	PxRigidDynamic* body = createDynamicRigidbody(position, rotation, userData, mat, geometry);
	body->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	return body;
}

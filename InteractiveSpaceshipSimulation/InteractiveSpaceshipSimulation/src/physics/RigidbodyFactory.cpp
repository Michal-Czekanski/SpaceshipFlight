#include "physics/RigidbodyFactory.h"

PxRigidDynamic* RigidbodyFactory::createShipRigidbody(glm::vec3 position, glm::quat rotation, void* shipPointer)
{
	PxPhysics* pxPhysics = Physics::getInstance()->getPxPhysics();
	PxScene* pxScene = Physics::getInstance()->getPxScene();

	PxRigidDynamic* shipBody = pxPhysics->createRigidDynamic(
		PxTransform(PhysxGLMConverter::vec3ToPxVec3(position), PhysxGLMConverter::quatToPxQuat(rotation)));
	
	PxMaterial* shipMaterial = pxPhysics->createMaterial(0.5, 0.5, 0.6);

	PxGeometry shipGeometry = PxBoxGeometry(1, 1, 1); // TODO
	PxShape* shipShape = pxPhysics->createShape(shipGeometry, *shipMaterial);
	shipBody->attachShape(*shipShape);
	shipShape->release();
	shipBody->userData = shipPointer;
	pxScene->addActor(*shipBody);
	return shipBody;
}

PxRigidDynamic* RigidbodyFactory::createAsteroidRigidbody(glm::vec3 position, glm::quat rotation, void* asteroidPointer)
{
	PxPhysics* pxPhysics = Physics::getInstance()->getPxPhysics();
	PxScene* pxScene = Physics::getInstance()->getPxScene();

	PxRigidDynamic* asteroidBody = pxPhysics->createRigidDynamic(
		PxTransform(PhysxGLMConverter::vec3ToPxVec3(position), PhysxGLMConverter::quatToPxQuat(rotation)));

	PxMaterial* asteroidMaterial = pxPhysics->createMaterial(0.5, 0.5, 0.6);

	PxGeometry asteroidGeometry = PxSphereGeometry(1); // TODO
	PxShape* asteroidShape = pxPhysics->createShape(asteroidGeometry, *asteroidMaterial);
	asteroidBody->attachShape(*asteroidShape);
	asteroidShape->release();
	asteroidBody->userData = asteroidPointer;
	pxScene->addActor(*asteroidBody);
	return asteroidBody;
}

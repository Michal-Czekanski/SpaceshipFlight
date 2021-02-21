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

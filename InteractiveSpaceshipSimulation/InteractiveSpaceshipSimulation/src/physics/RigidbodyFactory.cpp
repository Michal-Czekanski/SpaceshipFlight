#include "physics/RigidbodyFactory.h"

PxRigidDynamic* RigidbodyFactory::createShipRigidbody(glm::vec3 position, glm::quat rotation, void* shipPointer)
{
	Physics* p = Physics::getInstance();
	PxPhysics* pxP = p->getPxPhysics();
	PxScene* pxS = p->getPxScene();

	PxRigidDynamic* shipBody = pxP->createRigidDynamic(
		PxTransform(PhysxGLMConverter::vec3ToPxVec3(position), PhysxGLMConverter::quatToPxQuat(rotation)));
	
	PxMaterial* shipMaterial = pxP->createMaterial(0.5, 0.5, 0.6);

	PxGeometry shipGeometry = PxBoxGeometry(1, 1, 1); // TODO
	PxShape* shipShape = pxP->createShape(shipGeometry, *shipMaterial);
	shipBody->attachShape(*shipShape);
	shipShape->release();
	shipBody->userData = shipPointer;
	pxS->addActor(*shipBody);
	return shipBody;
}
